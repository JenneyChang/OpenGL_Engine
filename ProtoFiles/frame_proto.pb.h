// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: frame_proto.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_frame_5fproto_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_frame_5fproto_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021005 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include "bone_proto.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_frame_5fproto_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_frame_5fproto_2eproto {
  static const uint32_t offsets[];
};
class frame_proto_mssg;
struct frame_proto_mssgDefaultTypeInternal;
extern frame_proto_mssgDefaultTypeInternal _frame_proto_mssg_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::frame_proto_mssg* Arena::CreateMaybeMessage<::frame_proto_mssg>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class frame_proto_mssg final :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:frame_proto_mssg) */ {
 public:
  inline frame_proto_mssg() : frame_proto_mssg(nullptr) {}
  ~frame_proto_mssg() override;
  explicit PROTOBUF_CONSTEXPR frame_proto_mssg(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  frame_proto_mssg(const frame_proto_mssg& from);
  frame_proto_mssg(frame_proto_mssg&& from) noexcept
    : frame_proto_mssg() {
    *this = ::std::move(from);
  }

  inline frame_proto_mssg& operator=(const frame_proto_mssg& from) {
    CopyFrom(from);
    return *this;
  }
  inline frame_proto_mssg& operator=(frame_proto_mssg&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const frame_proto_mssg& default_instance() {
    return *internal_default_instance();
  }
  static inline const frame_proto_mssg* internal_default_instance() {
    return reinterpret_cast<const frame_proto_mssg*>(
               &_frame_proto_mssg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(frame_proto_mssg& a, frame_proto_mssg& b) {
    a.Swap(&b);
  }
  inline void Swap(frame_proto_mssg* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(frame_proto_mssg* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  frame_proto_mssg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<frame_proto_mssg>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)  final;
  void CopyFrom(const frame_proto_mssg& from);
  void MergeFrom(const frame_proto_mssg& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(frame_proto_mssg* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "frame_proto_mssg";
  }
  protected:
  explicit frame_proto_mssg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBonesFieldNumber = 3,
    kFrameNoFieldNumber = 1,
    kKeytimeFieldNumber = 2,
  };
  // repeated .bone_proto_mssg bones = 3;
  int bones_size() const;
  private:
  int _internal_bones_size() const;
  public:
  void clear_bones();
  ::bone_proto_mssg* mutable_bones(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::bone_proto_mssg >*
      mutable_bones();
  private:
  const ::bone_proto_mssg& _internal_bones(int index) const;
  ::bone_proto_mssg* _internal_add_bones();
  public:
  const ::bone_proto_mssg& bones(int index) const;
  ::bone_proto_mssg* add_bones();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::bone_proto_mssg >&
      bones() const;

  // uint32 frameNo = 1;
  void clear_frameno();
  uint32_t frameno() const;
  void set_frameno(uint32_t value);
  private:
  uint32_t _internal_frameno() const;
  void _internal_set_frameno(uint32_t value);
  public:

  // float keytime = 2;
  void clear_keytime();
  float keytime() const;
  void set_keytime(float value);
  private:
  float _internal_keytime() const;
  void _internal_set_keytime(float value);
  public:

  // @@protoc_insertion_point(class_scope:frame_proto_mssg)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::bone_proto_mssg > bones_;
    uint32_t frameno_;
    float keytime_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_frame_5fproto_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// frame_proto_mssg

// uint32 frameNo = 1;
inline void frame_proto_mssg::clear_frameno() {
  _impl_.frameno_ = 0u;
}
inline uint32_t frame_proto_mssg::_internal_frameno() const {
  return _impl_.frameno_;
}
inline uint32_t frame_proto_mssg::frameno() const {
  // @@protoc_insertion_point(field_get:frame_proto_mssg.frameNo)
  return _internal_frameno();
}
inline void frame_proto_mssg::_internal_set_frameno(uint32_t value) {
  
  _impl_.frameno_ = value;
}
inline void frame_proto_mssg::set_frameno(uint32_t value) {
  _internal_set_frameno(value);
  // @@protoc_insertion_point(field_set:frame_proto_mssg.frameNo)
}

// float keytime = 2;
inline void frame_proto_mssg::clear_keytime() {
  _impl_.keytime_ = 0;
}
inline float frame_proto_mssg::_internal_keytime() const {
  return _impl_.keytime_;
}
inline float frame_proto_mssg::keytime() const {
  // @@protoc_insertion_point(field_get:frame_proto_mssg.keytime)
  return _internal_keytime();
}
inline void frame_proto_mssg::_internal_set_keytime(float value) {
  
  _impl_.keytime_ = value;
}
inline void frame_proto_mssg::set_keytime(float value) {
  _internal_set_keytime(value);
  // @@protoc_insertion_point(field_set:frame_proto_mssg.keytime)
}

// repeated .bone_proto_mssg bones = 3;
inline int frame_proto_mssg::_internal_bones_size() const {
  return _impl_.bones_.size();
}
inline int frame_proto_mssg::bones_size() const {
  return _internal_bones_size();
}
inline ::bone_proto_mssg* frame_proto_mssg::mutable_bones(int index) {
  // @@protoc_insertion_point(field_mutable:frame_proto_mssg.bones)
  return _impl_.bones_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::bone_proto_mssg >*
frame_proto_mssg::mutable_bones() {
  // @@protoc_insertion_point(field_mutable_list:frame_proto_mssg.bones)
  return &_impl_.bones_;
}
inline const ::bone_proto_mssg& frame_proto_mssg::_internal_bones(int index) const {
  return _impl_.bones_.Get(index);
}
inline const ::bone_proto_mssg& frame_proto_mssg::bones(int index) const {
  // @@protoc_insertion_point(field_get:frame_proto_mssg.bones)
  return _internal_bones(index);
}
inline ::bone_proto_mssg* frame_proto_mssg::_internal_add_bones() {
  return _impl_.bones_.Add();
}
inline ::bone_proto_mssg* frame_proto_mssg::add_bones() {
  ::bone_proto_mssg* _add = _internal_add_bones();
  // @@protoc_insertion_point(field_add:frame_proto_mssg.bones)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::bone_proto_mssg >&
frame_proto_mssg::bones() const {
  // @@protoc_insertion_point(field_list:frame_proto_mssg.bones)
  return _impl_.bones_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_frame_5fproto_2eproto
