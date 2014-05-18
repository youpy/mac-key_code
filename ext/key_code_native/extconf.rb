require "mkmf"

extension_name = 'key_code_native'
dir_config(extension_name)

$LDFLAGS += ' -framework AppKit'

begin
  MACRUBY_VERSION # Only MacRuby has this constant.
  $CFLAGS += ' -fobjc-gc' # Enable MacOSX's GC for MacRuby
rescue
end

create_makefile(extension_name)
