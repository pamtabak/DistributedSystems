//
// Created by Eric Reis on 7/9/16.
//

#include <iostream>
#include <grpc++/grpc++.h>
#include <math.h>

#include "arithmetic.grpc.pb.h"

class ArithmeticImpl final : public arithmetic::Arithmetic::Service
{
public:
    grpc::Status Exp(grpc::ServerContext* context, const arithmetic::ArithmeticRequest* request,
                     arithmetic::ArithmeticReply* reply) override
    {
        std::cout << request->ByteSize() << std::endl;
        for(int i = 0, sz = request->vec_size(); i < sz; i++)
        {
            reply->add_vec(exp(request->vec(i)));
        }
        return grpc::Status::OK;
    }

    grpc::Status Log(grpc::ServerContext* context, const arithmetic::ArithmeticRequest* request,
                     arithmetic::ArithmeticReply* reply) override
    {
        for(int i = 0, sz = request->vec_size(); i < sz; i++)
        {
            reply->add_vec(log(request->vec(i)));
        }
        return grpc::Status::OK;
    }

    grpc::Status Pow(grpc::ServerContext* context, const arithmetic::ArithmeticRequest* request,
                     arithmetic::ArithmeticReply* reply) override
    {
        for(int i = 0, sz = request->vec_size(); i < sz; i++)
        {
            reply->add_vec(pow(request->vec(i), request->param()));
        }
        return grpc::Status::OK;
    }

    grpc::Status Sqrt(grpc::ServerContext* context, const arithmetic::ArithmeticRequest* request,
                     arithmetic::ArithmeticReply* reply) override
    {
        for(int i = 0, sz = request->vec_size(); i < sz; i++)
        {
            reply->add_vec(sqrt(request->vec(i)));
        }
        return grpc::Status::OK;
    }
};

void RunServer()
{
    std::string server_address("0.0.0.0:50051");
    ArithmeticImpl service;

    grpc::ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv)
{
    RunServer();
    return 0;
}