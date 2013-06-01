require 'lzf'
require 'zlib'

Dir.glob('./test_data/*.lzf').each do |f|
  hash = File.basename(f, '.lzf')
  # puts hash
  compressed = File.read(f)
  decompressed = LZF.decompress(compressed)
  # p decompressed
  if Zlib.adler32(decompressed) != hash.to_f
    puts "crc error: #{Zlib.adler32(decompressed)} != #{hash}"
    puts decompressed
  end

  if LZF.decompress(LZF.compress(decompressed)) != decompressed
    puts "#{hash} compressed != decompressed"
  end
end

puts "all ok"
