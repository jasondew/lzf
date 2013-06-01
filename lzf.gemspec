# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'lzf/version'

Gem::Specification.new do |spec|
  spec.name          = "lzf"
  spec.version       = Lzf::VERSION
  spec.authors       = ["glebtv"]
  spec.email         = ["glebtv@gmail.com"]
  spec.description   = %q{LZF compression with liblzf for ruby}
  spec.summary       = %q{LZF compression with liblzf for ruby}
  spec.homepage      = "https://github.com/glebtv/lzf"
  spec.license       = "MIT"

  spec.files         = `git ls-files`.split($/)
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  
  spec.extensions    = ['ext/extconf.rb']
  
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.3"
  spec.add_development_dependency "rake"
end
