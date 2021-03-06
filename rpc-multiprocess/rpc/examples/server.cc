//
// Created by Eric Reis on 7/6/16.
//

#include <iostream>
#include <grpc++/grpc++.h>

#include "adder.grpc.pb.h"

class AdderImpl final : public adder::Adder::Service
{
public:
    grpc::Status Add(grpc::ServerContext* context, const adder::AdderRequest* request,
                     adder::AdderReply* reply) override
    {
        int sum = 0;
        for(int i = 0, sz = request->values_size(); i < sz; i++)
        {
            request->set_values(i, 10); // -> this gives an error caused by the const declaration of the request variable
                                        //    error: "Non-const function 'set_values' is called on the const object"
            sum += request->values(i);
        }
        reply->set_sum(sum);
        return grpc::Status::OK;
    }
};

void RunServer()
{
    std::string server_address("0.0.0.0:50051");
    AdderImpl service;

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