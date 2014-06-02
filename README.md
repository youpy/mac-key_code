# mac-key_code

A key code library for mac.
It supports any keyboard layouts such as QWERTY, Dvorak etc.

It is based on http://stackoverflow.com/a/1971027 by [Michael](http://stackoverflow.com/users/217476/michael)

## Installation

Add this line to your application's Gemfile:

    gem 'mac-key_code'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install mac-key_code

## Usage

```ruby
require 'mac-key_code'

key_code = Mac::KeyCode.new(38)
key_code.to_s # => 'j'
```

## Contributing

1. Fork it ( http://github.com/youpy/mac-key_code/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
