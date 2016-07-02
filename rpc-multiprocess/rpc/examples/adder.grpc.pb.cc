// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: adder.proto

#include "adder.pb.h"
#include "adder.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace adder {

static const char* Adder_method_names[] = {
  "/adder.Adder/Add",
};

std::unique_ptr< Adder::Stub> Adder::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< Adder::Stub> stub(new Adder::Stub(channel));
  return stub;
}

Adder::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Add_(Adder_method_names[0], ::grpc::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Adder::Stub::Add(::grpc::ClientContext* context, const ::adder::AdderRequest& request, ::adder::AdderReply* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Add_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::adder::AdderReply>* Adder::Stub::AsyncAddRaw(::grpc::ClientContext* context, const ::adder::AdderRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::adder::AdderReply>(channel_.get(), cq, rpcmethod_Add_, context, request);
}

Adder::Service::Service() {
  (void)Adder_method_names;
  AddMethod(new ::grpc::RpcServiceMethod(
      Adder_method_names[0],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< Adder::Service, ::adder::AdderRequest, ::adder::AdderReply>(
          std::mem_fn(&Adder::Service::Add), this)));
}

Adder::Service::~Service() {
}

::grpc::Status Adder::Service::Add(::grpc::ServerContext* context, const ::adder::AdderRequest* request, ::adder::AdderReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace adder

