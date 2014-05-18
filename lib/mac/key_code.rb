require "mac/key_code/version"
require "key_code_native"

module Mac
  class KeyCode
    def initialize(key_code)
      @key_code = key_code
      @char = KeyCodeNative.key_code_to_char(@key_code)
    end

    def printable?
      @char =~ /^[a-zA-Z0-9.\*\+\/\-=\\\[\];,~` \t\n\r]/
    end

    def to_s
      @char
    end
  end
end
