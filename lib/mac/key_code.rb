require "mac/key_code/version"
require "key_code_native"

module Mac
  class KeyCode
    def initialize(key_code)
      @key_code = key_code
      @char = KeyCodeNative.key_code_to_char(@key_code)
    end

    def printable?
      @char =~ /^[[:print:]\s]+/
    end

    def to_s
      @char
    end
  end
end
