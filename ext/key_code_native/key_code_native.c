#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h> /* For kVK_ constants, and TIS functions. */
#include <ruby.h>

/* based on http://stackoverflow.com/a/1971027 */

VALUE CFString2RString(CFStringRef str) {
  int stringSize;
  char *tmpptr;
  VALUE result;

  stringSize = CFStringGetMaximumSizeForEncoding(CFStringGetLength(str), kCFStringEncodingUTF8) + 1;
  tmpptr = (char *)malloc(sizeof(char) * stringSize);
  CFStringGetCString(str, tmpptr, stringSize, kCFStringEncodingUTF8);
  result = rb_str_new2(tmpptr);
  free(tmpptr);

  return result;
}

/* Returns string representation of key, if it is printable.
 * Ownership follows the Create Rule; that is, it is the caller's
 * responsibility to release the returned object. */
CFStringRef createStringForKey(CGKeyCode keyCode)
{
  TISInputSourceRef currentKeyboard = TISCopyCurrentKeyboardInputSource();
  CFDataRef layoutData =
    TISGetInputSourceProperty(currentKeyboard,
                              kTISPropertyUnicodeKeyLayoutData);
  const UCKeyboardLayout *keyboardLayout =
    (const UCKeyboardLayout *)CFDataGetBytePtr(layoutData);

  UInt32 keysDown = 0;
  UniChar chars[4];
  UniCharCount realLength;

  UCKeyTranslate(keyboardLayout,
                 keyCode,
                 kUCKeyActionDisplay,
                 0,
                 LMGetKbdType(),
                 kUCKeyTranslateNoDeadKeysBit,
                 &keysDown,
                 sizeof(chars) / sizeof(chars[0]),
                 &realLength,
                 chars);
  CFRelease(currentKeyboard);

  return CFStringCreateWithCharacters(kCFAllocatorDefault, chars, 1);
}

/* Returns key code for given character via the above function, or UINT16_MAX
 * on error. */
CGKeyCode keyCodeForChar(const char c)
{
  static CFMutableDictionaryRef charToCodeDict = NULL;
  CGKeyCode code;
  UniChar character = c;
  CFStringRef charStr = NULL;

  /* Generate table of keycodes and characters. */
  if (charToCodeDict == NULL) {
    size_t i;
    charToCodeDict = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                               128,
                                               &kCFCopyStringDictionaryKeyCallBacks,
                                               NULL);
    if (charToCodeDict == NULL) return UINT16_MAX;

    /* Loop through every keycode (0 - 127) to find its current mapping. */
    for (i = 0; i < 128; ++i) {
      CFStringRef string = createStringForKey((CGKeyCode)i);
      if (string != NULL) {
        CFDictionaryAddValue(charToCodeDict, string, (const void *)i);
        CFRelease(string);
      }
    }
  }

  charStr = CFStringCreateWithCharacters(kCFAllocatorDefault, &character, 1);

  /* Our values may be NULL (0), so we need to use this function. */
  if (!CFDictionaryGetValueIfPresent(charToCodeDict, charStr,
                                     (const void **)&code)) {
    code = UINT16_MAX;
  }

  CFRelease(charStr);
  return code;
}

static VALUE mKeyCodeNative_key_code_to_char(int argc, VALUE *argv, VALUE self)
{
  VALUE key_code;

  int intKey_code;
  CFStringRef c;

  rb_scan_args(argc, argv, "1", &key_code);


  intKey_code = NUM2INT(key_code);

  c = createStringForKey((CGKeyCode)intKey_code);

  return CFString2RString(c);
}

void Init_key_code_native(void){
  VALUE rb_mMac, rb_mKeyCodeNative;

  rb_mMac = rb_define_module("Mac");
  rb_mKeyCodeNative = rb_define_module_under(rb_mMac, "KeyCodeNative");
  rb_define_singleton_method(rb_mKeyCodeNative, "key_code_to_char", mKeyCodeNative_key_code_to_char, -1);
}
