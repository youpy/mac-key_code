# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'mac/key_code/version'

Gem::Specification.new do |spec|
  spec.name          = "mac-key_code"
  spec.version       = Mac::KeyCode::VERSION
  spec.authors       = ["youpy"]
  spec.email         = ["youpy@buycheapviagraonlinenow.com"]
  spec.summary       = %q{A key code library for mac}
  spec.description   = %q{A key code library for mac. It supports any keyboard layouts such as QWERTY, Dvorak etc.}
  spec.homepage      = "https://github.com/youpy/mac-key_code"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0")
  spec.extensions    = ["ext/key_code_native/extconf.rb"]
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.5"
  spec.add_development_dependency "rake"
  spec.add_development_dependency "rspec", "~> 2.14"
end
