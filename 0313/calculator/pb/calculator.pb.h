// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: calculator.proto

#ifndef PROTOBUF_calculator_2eproto__INCLUDED
#define PROTOBUF_calculator_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_calculator_2eproto();
void protobuf_AssignDesc_calculator_2eproto();
void protobuf_ShutdownFile_calculator_2eproto();

class Calculator;

// ===================================================================

class Calculator : public ::google::protobuf::Message {
 public:
  Calculator();
  virtual ~Calculator();

  Calculator(const Calculator& from);

  inline Calculator& operator=(const Calculator& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Calculator& default_instance();

  void Swap(Calculator* other);

  // implements Message ----------------------------------------------

  Calculator* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Calculator& from);
  void MergeFrom(const Calculator& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required fixed32 op = 1;
  inline bool has_op() const;
  inline void clear_op();
  static const int kOpFieldNumber = 1;
  inline ::google::protobuf::uint32 op() const;
  inline void set_op(::google::protobuf::uint32 value);

  // required fixed32 lhs = 2;
  inline bool has_lhs() const;
  inline void clear_lhs();
  static const int kLhsFieldNumber = 2;
  inline ::google::protobuf::uint32 lhs() const;
  inline void set_lhs(::google::protobuf::uint32 value);

  // required fixed32 rhs = 3;
  inline bool has_rhs() const;
  inline void clear_rhs();
  static const int kRhsFieldNumber = 3;
  inline ::google::protobuf::uint32 rhs() const;
  inline void set_rhs(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Calculator)
 private:
  inline void set_has_op();
  inline void clear_has_op();
  inline void set_has_lhs();
  inline void clear_has_lhs();
  inline void set_has_rhs();
  inline void clear_has_rhs();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 op_;
  ::google::protobuf::uint32 lhs_;
  ::google::protobuf::uint32 rhs_;
  friend void  protobuf_AddDesc_calculator_2eproto();
  friend void protobuf_AssignDesc_calculator_2eproto();
  friend void protobuf_ShutdownFile_calculator_2eproto();

  void InitAsDefaultInstance();
  static Calculator* default_instance_;
};
// ===================================================================


// ===================================================================

// Calculator

// required fixed32 op = 1;
inline bool Calculator::has_op() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Calculator::set_has_op() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Calculator::clear_has_op() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Calculator::clear_op() {
  op_ = 0u;
  clear_has_op();
}
inline ::google::protobuf::uint32 Calculator::op() const {
  // @@protoc_insertion_point(field_get:Calculator.op)
  return op_;
}
inline void Calculator::set_op(::google::protobuf::uint32 value) {
  set_has_op();
  op_ = value;
  // @@protoc_insertion_point(field_set:Calculator.op)
}

// required fixed32 lhs = 2;
inline bool Calculator::has_lhs() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Calculator::set_has_lhs() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Calculator::clear_has_lhs() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Calculator::clear_lhs() {
  lhs_ = 0u;
  clear_has_lhs();
}
inline ::google::protobuf::uint32 Calculator::lhs() const {
  // @@protoc_insertion_point(field_get:Calculator.lhs)
  return lhs_;
}
inline void Calculator::set_lhs(::google::protobuf::uint32 value) {
  set_has_lhs();
  lhs_ = value;
  // @@protoc_insertion_point(field_set:Calculator.lhs)
}

// required fixed32 rhs = 3;
inline bool Calculator::has_rhs() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Calculator::set_has_rhs() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Calculator::clear_has_rhs() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Calculator::clear_rhs() {
  rhs_ = 0u;
  clear_has_rhs();
}
inline ::google::protobuf::uint32 Calculator::rhs() const {
  // @@protoc_insertion_point(field_get:Calculator.rhs)
  return rhs_;
}
inline void Calculator::set_rhs(::google::protobuf::uint32 value) {
  set_has_rhs();
  rhs_ = value;
  // @@protoc_insertion_point(field_set:Calculator.rhs)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_calculator_2eproto__INCLUDED
