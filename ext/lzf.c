#include <ruby.h>

#include "lib/lzf_c.c"
#include "lib/lzf_d.c"

static VALUE rb_mLZF;
static VALUE rb_eLZF;

static VALUE lzfruby_compress(int argc, VALUE *argv, VALUE self) {
  VALUE src, dst;
  unsigned int output_length, result;

  rb_scan_args(argc, argv, "1", &src);

  StringValue(src);

  output_length = (unsigned int) (RSTRING_LEN(src) * 1.05);

  dst = rb_str_new(NULL, output_length);

  result = lzf_compress(RSTRING_PTR(src), RSTRING_LEN(src), RSTRING_PTR(dst), &output_length);
  if (result == 0) {
    rb_raise(rb_eLZF, "ERROR");
    return Qnil;
  } else {
    StringValue(dst);
    rb_str_resize(dst, result);
    return dst;
  }
}

static VALUE lzfruby_decompress(int argc, VALUE *argv, VALUE self) {
  VALUE src, dst;
  rb_scan_args(argc, argv, "1", &src);
  StringValue(src);
  unsigned int result, i = 1, buffer_size = 1024;

  dst = rb_str_new(NULL, buffer_size);

  // Pretty inefficient for large data, but PHP does it the same way
  do {
    buffer_size *= i++;
    rb_str_resize(dst, buffer_size);
    result = lzf_decompress(RSTRING_PTR(src), RSTRING_LEN(src), RSTRING_PTR(dst), buffer_size);
  } while (result == 0 && errno == E2BIG);

  if (result == 0) {
    if (errno == EINVAL) {
      rb_raise(rb_eLZF, "LZF error: compressed data corrupted");
      return Qnil;
    } else {
      rb_raise(rb_eLZF, printf("LZF error %d", errno));
      return Qnil;
    }
  } else {
    StringValue(dst);
    rb_str_resize(dst, result);
    return dst;
  }
}


void Init_lzf(void) {
  rb_mLZF = rb_define_module("LZF");
  rb_eLZF = rb_define_class_under(rb_mLZF, "Error", rb_eStandardError);

  rb_define_singleton_method(rb_mLZF, "compress", lzfruby_compress, -1);
  rb_define_singleton_method(rb_mLZF, "decompress", lzfruby_decompress, -1);
}

