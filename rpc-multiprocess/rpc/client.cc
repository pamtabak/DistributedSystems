//
// Created by Eric Reis on 7/6/16.
//

#include <iostream>
#include <grpc++/grpc++.h>

#include "arithmetic.grpc.pb.h"

class ArithmeticClient
{
public:
    ArithmeticClient(std::shared_ptr<grpc::Channel> channel) : stub_(arithmetic::Arithmetic::NewStub(channel)) {}

    void Exp(double* vec, int sz)
    {
        // Data we are sending to the server.
        arithmetic::ArithmeticRequest request;
        for (int i = 0; i < sz; i++)
        {
            request.add_vec(vec[i]);
        }

        // Container for the data we expect from the server.
        arithmetic::ArithmeticReply reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // The actual RPC.
        grpc::Status status = stub_->Exp(&context, request, &reply);

        // Act upon its status.
        if (status.ok())
        {
            // vec = reply.mutable_vec()->mutable_data(); -> doesn't change the vec ????
            for (int i = 0; i < sz; i++ )
            {
                vec[i] = reply.vec(i);
            }
        }
        else
        {
            std::cout << "RPC failed" << std::endl;
        }
    }

    void Log(double* vec, int sz)
    {
        // Data we are sending to the server.
        arithmetic::ArithmeticRequest request;
        for (int i = 0; i < sz; i++)
        {
            request.add_vec(vec[i]);
        }

        // Container for the data we expect from the server.
        arithmetic::ArithmeticReply reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // The actual RPC.
        grpc::Status status = stub_->Log(&context, request, &reply);

        // Act upon its status.
        if (status.ok())
        {
            for (int i = 0; i < sz; i++ )
            {
                vec[i] = reply.vec(i);
            }
        }
        else
        {
            std::cout << "RPC failed" << std::endl;
        }
    }

    void Pow(double* vec, int sz, double param)
    {
        // Data we are sending to the server.
        arithmetic::ArithmeticRequest request;
        for (int i = 0; i < sz; i++)
        {
            request.add_vec(vec[i]);
        }
        request.set_param(param);

        // Container for the data we expect from the server.
        arithmetic::ArithmeticReply reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // The actual RPC.
        grpc::Status status = stub_->Exp(&context, request, &reply);

        // Act upon its status.
        if (status.ok())
        {
            for (int i = 0; i < sz; i++ )
            {
                vec[i] = reply.vec(i);
            }
        }
        else
        {
            std::cout << "RPC failed" << std::endl;
        }
    }

    void Sqrt(double* vec, int sz)
    {
        // Data we are sending to the server.
        arithmetic::ArithmeticRequest request;
        for (int i = 0; i < sz; i++)
        {
            request.add_vec(vec[i]);
        }

        // Container for the data we expect from the server.
        arithmetic::ArithmeticReply reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // The actual RPC.
        grpc::Status status = stub_->Sqrt(&context, request, &reply);

        // Act upon its status.
        if (status.ok())
        {
            for (int i = 0; i < sz; i++ )
            {
                vec[i] = reply.vec(i);
            }
        }
        else
        {
            std::cout << "RPC failed" << std::endl;
        }
    }

private:
    std::unique_ptr<arithmetic::Arithmetic::Stub> stub_;
};

int main(int argc, char** argv)
{
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    ArithmeticClient arithmetic(grpc::CreateChannel("localhost:50051",
                                          grpc::InsecureChannelCredentials()));

    double vec[] = {1,2,3,4,5};

    for (int i = 0; i < 5; i++)
    {
        std::cout << vec[i] << std::endl;
    }

    std::cout << std::endl << std::endl;

    arithmetic.Log(vec, 5);

    for (int i = 0; i < 5; i++)
    {
        std::cout << vec[i] << std::endl;
    }

    return 0;
}