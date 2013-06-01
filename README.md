# Lzf

LZF compression with liblzf for ruby


## Installation

Add this line to your application's Gemfile:

    gem 'lzf'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install lzf

## Usage

    > require 'lzf'
    > compressed = LZF.compress('testtesttesttesttest')
     => "\x04testt\xE0\x04\x03\x01st"
    > LZF.decompress(compressed)
     => "testtesttesttesttest"

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

## Credits

(c) 2013 GlebTV. MIT license

Contains LibLZF (BSD-type-license): http://oldhome.schmorp.de/marc/liblzf.html

Loosely based on https://bitbucket.org/winebarrel/lzf-ruby/overview (Copyright (c) 2008 SUGAWARA Genki <sgwr_dts@yahoo.co.jp>,
BSD License) which won't compile properly for me.
