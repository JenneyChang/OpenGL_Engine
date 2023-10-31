// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: key_proto.proto

#include "key_proto.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR key_proto_mssg::key_proto_mssg(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.key_)*/0u
  , /*decltype(_impl_.x_)*/0u
  , /*decltype(_impl_.y_)*/0u
  , /*decltype(_impl_.w_)*/0u
  , /*decltype(_impl_.h_)*/0u
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct key_proto_mssgDefaultTypeInternal {
  PROTOBUF_CONSTEXPR key_proto_mssgDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~key_proto_mssgDefaultTypeInternal() {}
  union {
    key_proto_mssg _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 key_proto_mssgDefaultTypeInternal _key_proto_mssg_default_instance_;

// ===================================================================

class key_proto_mssg::_Internal {
 public:
};

key_proto_mssg::key_proto_mssg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:key_proto_mssg)
}
key_proto_mssg::key_proto_mssg(const key_proto_mssg& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite() {
  key_proto_mssg* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.key_){}
    , decltype(_impl_.x_){}
    , decltype(_impl_.y_){}
    , decltype(_impl_.w_){}
    , decltype(_impl_.h_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
  ::memcpy(&_impl_.key_, &from._impl_.key_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.h_) -
    reinterpret_cast<char*>(&_impl_.key_)) + sizeof(_impl_.h_));
  // @@protoc_insertion_point(copy_constructor:key_proto_mssg)
}

inline void key_proto_mssg::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.key_){0u}
    , decltype(_impl_.x_){0u}
    , decltype(_impl_.y_){0u}
    , decltype(_impl_.w_){0u}
    , decltype(_impl_.h_){0u}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

key_proto_mssg::~key_proto_mssg() {
  // @@protoc_insertion_point(destructor:key_proto_mssg)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<std::string>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void key_proto_mssg::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void key_proto_mssg::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void key_proto_mssg::Clear() {
// @@protoc_insertion_point(message_clear_start:key_proto_mssg)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.key_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.h_) -
      reinterpret_cast<char*>(&_impl_.key_)) + sizeof(_impl_.h_));
  _internal_metadata_.Clear<std::string>();
}

const char* key_proto_mssg::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 key = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.key_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 x = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.x_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 y = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.y_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 w = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.w_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 h = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          _impl_.h_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<std::string>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* key_proto_mssg::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:key_proto_mssg)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 key = 1;
  if (this->_internal_key() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(1, this->_internal_key(), target);
  }

  // uint32 x = 2;
  if (this->_internal_x() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(2, this->_internal_x(), target);
  }

  // uint32 y = 3;
  if (this->_internal_y() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(3, this->_internal_y(), target);
  }

  // uint32 w = 4;
  if (this->_internal_w() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(4, this->_internal_w(), target);
  }

  // uint32 h = 5;
  if (this->_internal_h() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(5, this->_internal_h(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = stream->WriteRaw(_internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).data(),
        static_cast<int>(_internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).size()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:key_proto_mssg)
  return target;
}

size_t key_proto_mssg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:key_proto_mssg)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint32 key = 1;
  if (this->_internal_key() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_key());
  }

  // uint32 x = 2;
  if (this->_internal_x() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_x());
  }

  // uint32 y = 3;
  if (this->_internal_y() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_y());
  }

  // uint32 w = 4;
  if (this->_internal_w() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_w());
  }

  // uint32 h = 5;
  if (this->_internal_h() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_h());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    total_size += _internal_metadata_.unknown_fields<std::string>(::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString).size();
  }
  int cached_size = ::_pbi::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void key_proto_mssg::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::_pbi::DownCast<const key_proto_mssg*>(
      &from));
}

void key_proto_mssg::MergeFrom(const key_proto_mssg& from) {
  key_proto_mssg* const _this = this;
  // @@protoc_insertion_point(class_specific_merge_from_start:key_proto_mssg)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_key() != 0) {
    _this->_internal_set_key(from._internal_key());
  }
  if (from._internal_x() != 0) {
    _this->_internal_set_x(from._internal_x());
  }
  if (from._internal_y() != 0) {
    _this->_internal_set_y(from._internal_y());
  }
  if (from._internal_w() != 0) {
    _this->_internal_set_w(from._internal_w());
  }
  if (from._internal_h() != 0) {
    _this->_internal_set_h(from._internal_h());
  }
  _this->_internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
}

void key_proto_mssg::CopyFrom(const key_proto_mssg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:key_proto_mssg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool key_proto_mssg::IsInitialized() const {
  return true;
}

void key_proto_mssg::InternalSwap(key_proto_mssg* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(key_proto_mssg, _impl_.h_)
      + sizeof(key_proto_mssg::_impl_.h_)
      - PROTOBUF_FIELD_OFFSET(key_proto_mssg, _impl_.key_)>(
          reinterpret_cast<char*>(&_impl_.key_),
          reinterpret_cast<char*>(&other->_impl_.key_));
}

std::string key_proto_mssg::GetTypeName() const {
  return "key_proto_mssg";
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::key_proto_mssg*
Arena::CreateMaybeMessage< ::key_proto_mssg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::key_proto_mssg >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>