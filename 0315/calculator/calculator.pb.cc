// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: calculator.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "calculator.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* Request_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Request_reflection_ = NULL;
const ::google::protobuf::Descriptor* Response_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Response_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_calculator_2eproto() {
  protobuf_AddDesc_calculator_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "calculator.proto");
  GOOGLE_CHECK(file != NULL);
  Request_descriptor_ = file->message_type(0);
  static const int Request_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Request, lhs_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Request, rhs_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Request, op_),
  };
  Request_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Request_descriptor_,
      Request::default_instance_,
      Request_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Request, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Request, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Request));
  Response_descriptor_ = file->message_type(1);
  static const int Response_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, result_),
  };
  Response_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Response_descriptor_,
      Response::default_instance_,
      Response_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Response));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_calculator_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Request_descriptor_, &Request::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Response_descriptor_, &Response::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_calculator_2eproto() {
  delete Request::default_instance_;
  delete Request_reflection_;
  delete Response::default_instance_;
  delete Response_reflection_;
}

void protobuf_AddDesc_calculator_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020calculator.proto\"/\n\007Request\022\013\n\003lhs\030\001 \002"
    "(\005\022\013\n\003rhs\030\002 \002(\005\022\n\n\002op\030\003 \002(\005\"\032\n\010Response\022"
    "\016\n\006result\030\001 \002(\003", 95);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "calculator.proto", &protobuf_RegisterTypes);
  Request::default_instance_ = new Request();
  Response::default_instance_ = new Response();
  Request::default_instance_->InitAsDefaultInstance();
  Response::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_calculator_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_calculator_2eproto {
  StaticDescriptorInitializer_calculator_2eproto() {
    protobuf_AddDesc_calculator_2eproto();
  }
} static_descriptor_initializer_calculator_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Request::kLhsFieldNumber;
const int Request::kRhsFieldNumber;
const int Request::kOpFieldNumber;
#endif  // !_MSC_VER

Request::Request()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Request)
}

void Request::InitAsDefaultInstance() {
}

Request::Request(const Request& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Request)
}

void Request::SharedCtor() {
  _cached_size_ = 0;
  lhs_ = 0;
  rhs_ = 0;
  op_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Request::~Request() {
  // @@protoc_insertion_point(destructor:Request)
  SharedDtor();
}

void Request::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Request::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Request::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Request_descriptor_;
}

const Request& Request::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_calculator_2eproto();
  return *default_instance_;
}

Request* Request::default_instance_ = NULL;

Request* Request::New() const {
  return new Request;
}

void Request::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Request*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(lhs_, op_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Request::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Request)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 lhs = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &lhs_)));
          set_has_lhs();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_rhs;
        break;
      }

      // required int32 rhs = 2;
      case 2: {
        if (tag == 16) {
         parse_rhs:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &rhs_)));
          set_has_rhs();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_op;
        break;
      }

      // required int32 op = 3;
      case 3: {
        if (tag == 24) {
         parse_op:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &op_)));
          set_has_op();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Request)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Request)
  return false;
#undef DO_
}

void Request::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Request)
  // required int32 lhs = 1;
  if (has_lhs()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->lhs(), output);
  }

  // required int32 rhs = 2;
  if (has_rhs()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->rhs(), output);
  }

  // required int32 op = 3;
  if (has_op()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->op(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Request)
}

::google::protobuf::uint8* Request::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Request)
  // required int32 lhs = 1;
  if (has_lhs()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->lhs(), target);
  }

  // required int32 rhs = 2;
  if (has_rhs()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->rhs(), target);
  }

  // required int32 op = 3;
  if (has_op()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->op(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Request)
  return target;
}

int Request::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 lhs = 1;
    if (has_lhs()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->lhs());
    }

    // required int32 rhs = 2;
    if (has_rhs()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->rhs());
    }

    // required int32 op = 3;
    if (has_op()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->op());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Request::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Request* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Request*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Request::MergeFrom(const Request& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_lhs()) {
      set_lhs(from.lhs());
    }
    if (from.has_rhs()) {
      set_rhs(from.rhs());
    }
    if (from.has_op()) {
      set_op(from.op());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Request::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Request::CopyFrom(const Request& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Request::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void Request::Swap(Request* other) {
  if (other != this) {
    std::swap(lhs_, other->lhs_);
    std::swap(rhs_, other->rhs_);
    std::swap(op_, other->op_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Request::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Request_descriptor_;
  metadata.reflection = Request_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Response::kResultFieldNumber;
#endif  // !_MSC_VER

Response::Response()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Response)
}

void Response::InitAsDefaultInstance() {
}

Response::Response(const Response& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Response)
}

void Response::SharedCtor() {
  _cached_size_ = 0;
  result_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Response::~Response() {
  // @@protoc_insertion_point(destructor:Response)
  SharedDtor();
}

void Response::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Response::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Response::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Response_descriptor_;
}

const Response& Response::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_calculator_2eproto();
  return *default_instance_;
}

Response* Response::default_instance_ = NULL;

Response* Response::New() const {
  return new Response;
}

void Response::Clear() {
  result_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Response::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Response)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int64 result = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &result_)));
          set_has_result();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Response)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Response)
  return false;
#undef DO_
}

void Response::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Response)
  // required int64 result = 1;
  if (has_result()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->result(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Response)
}

::google::protobuf::uint8* Response::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Response)
  // required int64 result = 1;
  if (has_result()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->result(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Response)
  return target;
}

int Response::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int64 result = 1;
    if (has_result()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->result());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Response::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Response* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Response*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Response::MergeFrom(const Response& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_result()) {
      set_result(from.result());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Response::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Response::CopyFrom(const Response& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Response::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void Response::Swap(Response* other) {
  if (other != this) {
    std::swap(result_, other->result_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Response::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Response_descriptor_;
  metadata.reflection = Response_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)