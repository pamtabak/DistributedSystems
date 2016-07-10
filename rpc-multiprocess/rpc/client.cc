//
// Created by Eric Reis on 7/6/16.
//

#include <iostream>
#include <grpc++/grpc++.h>

std::chrono::high_resolution_clock::time_point startTime;

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

struct args
{
    int id;
    double* vec;
    int rangeFrom;
    int rangeTo;
};

double random(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

void *test(void* arguments)
{
    struct args* args = (struct args *) arguments;
    int sz = args->rangeTo - args->rangeFrom;
    double* v = new double[sz];
    for (int i = 0; i < sz; i++)
    {
        v[i] = args->vec[args->rangeFrom + i];
    }

    ArithmeticClient arithmetic(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    arithmetic.Exp(v, sz);

    for (int i = 0; i < sz; i++)
    {
        args->vec[args->rangeFrom + i] = v[i];
    }
}

int main(int argc, const char* argv[])
{
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
//    ArithmeticClient arithmetic(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    startTime = std::chrono::high_resolution_clock::now();

    if(argc != 3)
    {
        std::cout << "Wrong parameters" << std::endl;
        exit(-1);
    }

    // Extracting info regarding number of threads and size of vector, passed as parameters to this program
    int n = atoi(argv[1]); // vector size
    int k = atoi(argv[2]); // number of threads

    // Initializing seed
    time_t seed = time(NULL);
    srand(seed);

    // Initializing vector
    double *v = new double[n];
    for (int i = 0; i < n; i++)
    {
        v[i] = random(1, 10);
    }

    // Creating threads
    pthread_t *threads = (pthread_t *) malloc(k * sizeof(pthread_t));
    struct args **tArgs  = (struct args **) malloc(k * sizeof(struct args *));
    int delta = n / k;
    int lastValue = 0;
    for (int i = 0; i < k; i++)
    {
        tArgs[i]            = (args *) malloc(sizeof(args));
        tArgs[i]->id        = i + 1;
        tArgs[i]->vec       = v;
        tArgs[i]->rangeFrom = lastValue;
        tArgs[i]->rangeTo   = lastValue + delta;

        lastValue += delta;
        if (i == (k - 1))
        {
            tArgs[i]->rangeTo = n;
        }

        pthread_create(&threads[i], NULL, test, (void *) tArgs[i]);
    }

    // Thread Join
    for(int i = 0; i < k; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    delete [] v, threads;

    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> endTimeSpan              = std::chrono::duration_cast< std::chrono::duration<double> >(endTime - startTime);
    printf("end: %lf secs\n", endTimeSpan.count());

    return 0;
}