// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: arithmetic.proto

#include "arithmetic.pb.h"
#include "arithmetic.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace arithmetic {

static const char* Arithmetic_method_names[] = {
  "/arithmetic.Arithmetic/Exp",
  "/arithmetic.Arithmetic/Log",
  "/arithmetic.Arithmetic/Pow",
  "/arithmetic.Arithmetic/Sqrt",
};

std::unique_ptr< Arithmetic::Stub> Arithmetic::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< Arithmetic::Stub> stub(new Arithmetic::Stub(channel));
  return stub;
}

Arithmetic::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Exp_(Arithmetic_method_names[0], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Log_(Arithmetic_method_names[1], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Pow_(Arithmetic_method_names[2], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Sqrt_(Arithmetic_method_names[3], ::grpc::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Arithmetic::Stub::Exp(::grpc::ClientContext* context, const ::arithmetic::ArithmeticRequest& request, ::arithmetic::ArithmeticReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Exp_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::arithmetic::ArithmeticReply>* Arithmetic::Stub::AsyncExpRaw(::grpc::ClientContext* context, const ::arithmetic::ArithmeticRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::arithmetic::ArithmeticReply>(channel_.get(), cq, rpcmethod_Exp_, context, request);
}

::grpc::Status Arithmetic::Stub::Log(::grpc::ClientContext* context, const ::arithmetic::ArithmeticRequest& request, ::arithmetic::ArithmeticReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Log_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::arithmetic::ArithmeticReply>* Arithmetic::Stub::AsyncLogRaw(::grpc::ClientContext* context, const ::arithmetic::ArithmeticRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::arithmetic::ArithmeticReply>(channel_.get(), cq, rpcmethod_Log_, context, request);
}

::grpc::Status Arithmetic::Stub::Pow(::grpc::ClientContext* context, const ::arithmetic::ArithmeticRequest& request, ::arithmetic::ArithmeticReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Pow_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::arithmetic::ArithmeticReply>* Arithmetic::Stub::AsyncPowRaw(::grpc::ClientContext* context, const ::arithmetic::ArithmeticRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::arithmetic::ArithmeticReply>(channel_.get(), cq, rpcmethod_Pow_, context, request);
}

::grpc::Status Arithmetic::Stub::Sqrt(::grpc::ClientContext* context, const ::arithmetic::ArithmeticRequest& request, ::arithmetic::ArithmeticReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Sqrt_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::arithmetic::ArithmeticReply>* Arithmetic::Stub::AsyncSqrtRaw(::grpc::ClientContext* context, const ::arithmetic::ArithmeticRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::arithmetic::ArithmeticReply>(channel_.get(), cq, rpcmethod_Sqrt_, context, request);
}

Arithmetic::Service::Service() {
  (void)Arithmetic_method_names;
  AddMethod(new ::grpc::RpcServiceMethod(
      Arithmetic_method_names[0],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< Arithmetic::Service, ::arithmetic::ArithmeticRequest, ::arithmetic::ArithmeticReply>(
          std::mem_fn(&Arithmetic::Service::Exp), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      Arithmetic_method_names[1],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< Arithmetic::Service, ::arithmetic::ArithmeticRequest, ::arithmetic::ArithmeticReply>(
          std::mem_fn(&Arithmetic::Service::Log), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      Arithmetic_method_names[2],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< Arithmetic::Service, ::arithmetic::ArithmeticRequest, ::arithmetic::ArithmeticReply>(
          std::mem_fn(&Arithmetic::Service::Pow), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      Arithmetic_method_names[3],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< Arithmetic::Service, ::arithmetic::ArithmeticRequest, ::arithmetic::ArithmeticReply>(
          std::mem_fn(&Arithmetic::Service::Sqrt), this)));
}

Arithmetic::Service::~Service() {
}

::grpc::Status Arithmetic::Service::Exp(::grpc::ServerContext* context, const ::arithmetic::ArithmeticRequest* request, ::arithmetic::ArithmeticReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Arithmetic::Service::Log(::grpc::ServerContext* context, const ::arithmetic::ArithmeticRequest* request, ::arithmetic::ArithmeticReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Arithmetic::Service::Pow(::grpc::ServerContext* context, const ::arithmetic::ArithmeticRequest* request, ::arithmetic::ArithmeticReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Arithmetic::Service::Sqrt(::grpc::ServerContext* context, const ::arithmetic::ArithmeticRequest* request, ::arithmetic::ArithmeticReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace arithmetic

