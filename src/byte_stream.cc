#include "byte_stream.hh"
#include <string_view>

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity ), closed_( false ), buffer_(), bytes_pushed_( 0 ), bytes_popped_( 0 )
{}

bool Writer::is_closed() const
{
  return closed_;
}

void Writer::push( string data )
{
  uint64_t space = available_capacity();
  // (void)data;
  uint64_t push_size = min( space, (uint64_t)data.size() );
  for ( uint64_t i = 0; i < push_size; i++ ) {
    buffer_.push_back( data[i] );
  }
  bytes_pushed_ += push_size;
  return;
}

void Writer::close()
{
  closed_ = true;
  return;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  return closed_ && buffer_.empty();
}

uint64_t Reader::bytes_popped() const
{
  return bytes_popped_;
}

string_view Reader::peek() const
{
  return string_view( buffer_.data(), buffer_.size() );
}

void Reader::pop( uint64_t len )
{
  uint64_t pop_size = min( len, (uint64_t)buffer_.size() );
  buffer_.erase( buffer_.begin(), buffer_.begin() + pop_size );
  bytes_popped_ += pop_size;
  return;
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}
