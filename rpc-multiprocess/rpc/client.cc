//
// Created by Eric Reis on 7/6/16.
//

#include <iostream>
#include <grpc++/grpc++.h>

std::chrono::high_resolution_clock::time_point startTime;

#include "arithmetic.grpc.pb.h"

#define MAX_MESSAGE_BYTES 32000000

class ArithmeticClient
{
public:
    ArithmeticClient(std::shared_ptr<grpc::Channel> channel) : stub_(arithmetic::Arithmetic::NewStub(channel)) {}

    void Exp(double* vec, int sz)
    {
        // Data we are sending to the server.
        arithmetic::ArithmeticRequest request;

        int req_i = 0, rep_i = 0;
        while (req_i < sz)
        {
            request.clear_vec();
            while (req_i < sz && request.ByteSize() < MAX_MESSAGE_BYTES)
            {
                request.add_vec(vec[req_i]);
                req_i++;
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
                for (int i = 0, vec_sz = reply.vec_size(); i < vec_sz; i++ )
                {
                    vec[rep_i] = reply.vec(i);
                    rep_i++;
                }
            }
            else
            {
                std::cout << "RPC failed" << std::endl;
            }
        }
    }

    void Log(double* vec, int sz)
    {
        // Data we are sending to the server.
        arithmetic::ArithmeticRequest request;

        int req_i = 0, rep_i = 0;
        while (req_i < sz)
        {
            request.clear_vec();
            while (req_i < sz && request.ByteSize() < MAX_MESSAGE_BYTES)
            {
                request.add_vec(vec[req_i]);
                req_i++;
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
                for (int i = 0, vec_sz = reply.vec_size(); i < vec_sz; i++ )
                {
                    vec[rep_i] = reply.vec(i);
                    rep_i++;
                }
            }
            else
            {
                std::cout << "RPC failed" << std::endl;
            }
        }
    }

    void Pow(double* vec, int sz, double param)
    {
        // Data we are sending to the server.
        arithmetic::ArithmeticRequest request;

        int req_i = 0, rep_i = 0;
        while (req_i < sz)
        {
            request.clear_vec();
            while (req_i < sz && request.ByteSize() < MAX_MESSAGE_BYTES)
            {
                request.add_vec(vec[req_i]);
                req_i++;
            }

            // Container for the data we expect from the server.
            arithmetic::ArithmeticReply reply;

            // Context for the client. It could be used to convey extra information to
            // the server and/or tweak certain RPC behaviors.
            grpc::ClientContext context;

            // The actual RPC.
            grpc::Status status = stub_->Pow(&context, request, &reply);

            // Act upon its status.
            if (status.ok())
            {
                for (int i = 0, vec_sz = reply.vec_size(); i < vec_sz; i++ )
                {
                    vec[rep_i] = reply.vec(i);
                    rep_i++;
                }
            }
            else
            {
                std::cout << "RPC failed" << std::endl;
            }
        }
    }

    void Sqrt(double* vec, int sz)
    {
        // Data we are sending to the server.
        arithmetic::ArithmeticRequest request;

        int req_i = 0, rep_i = 0;
        while (req_i < sz)
        {
            request.clear_vec();
            while (req_i < sz && request.ByteSize() < MAX_MESSAGE_BYTES)
            {
                request.add_vec(vec[req_i]);
                req_i++;
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
                for (int i = 0, vec_sz = reply.vec_size(); i < vec_sz; i++ )
                {
                    vec[rep_i] = reply.vec(i);
                    rep_i++;
                }
            }
            else
            {
                std::cout << "RPC failed" << std::endl;
            }
        }
    }

private:
    std::unique_ptr<arithmetic::Arithmetic::Stub> stub_;
};

struct args
{
    double* vec;
    int rangeFrom;
    int rangeTo;
    std::string op;
};

double random(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

void *func(void* arguments)
{
    struct args* args = (struct args *) arguments;
    int sz = args->rangeTo - args->rangeFrom;
    double* v = new double[sz];
    for (int i = 0; i < sz; i++)
    {
        v[i] = args->vec[args->rangeFrom + i];
    }

    ArithmeticClient arithmetic(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));


    if (args->op == "exp")
    {
        arithmetic.Exp(v, sz);
    }
    else if (args->op == "log")
    {
        arithmetic.Log(v, sz);
    }
    else if (args->op == "pow2")
    {
        arithmetic.Pow(v, sz, 2);
    }
    else if (args->op == "sqrt")
    {
        arithmetic.Sqrt(v, sz);
    }
    else
    {
        printf("Undefined Operation\n");
        pthread_exit(NULL);
    }

    for (int i = 0; i < sz; i++)
    {
        args->vec[args->rangeFrom + i] = v[i];
    }
}

int main(int argc, const char* argv[])
{
    startTime = std::chrono::high_resolution_clock::now();

    if(argc != 4)
    {
        std::cout << "Wrong parameters" << std::endl;
        exit(-1);
    }

    // Extracting info regarding number of threads and size of vector, passed as parameters to this program
    int n = atoi(argv[1]); // vector size
    int k = atoi(argv[2]); // number of threads
    std::string op = argv[3]; // operation to be done

    // Initializing seed
    time_t seed = time(NULL);
    srand(seed);

    // Initializing vector
    double *v = new double[n];
    for (int i = 0; i < n; i++)
    {
        v[i] = random(1, 100);
    }

    // Creating threads
    pthread_t *threads = (pthread_t *) malloc(k * sizeof(pthread_t));
    struct args **tArgs  = (struct args **) malloc(k * sizeof(struct args *));
    int delta = n / k;
    int lastValue = 0;
    for (int i = 0; i < k; i++)
    {
        tArgs[i]            = (args *) malloc(sizeof(args));
        tArgs[i]->vec       = v;
        tArgs[i]->rangeFrom = lastValue;
        tArgs[i]->rangeTo   = lastValue + delta;
        tArgs[i]->op        = op;

        lastValue += delta;
        if (i == (k - 1))
        {
            tArgs[i]->rangeTo = n;
        }

        pthread_create(&threads[i], NULL, func, (void *) tArgs[i]);
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