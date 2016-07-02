#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "adder.grpc.pb.h"
class AdderClient
{
public:
	AdderClient(std::shared_ptr<grpc::Channel> channel) : stub_(adder::Adder::NewStub(channel)) {}

	int Add(const int a, const int b) {
		// Data we are sending to the server.
		adder::AdderRequest request;
		request.set_a(a);
		request.set_b(b);

		// Container for the data we expect from the server.
		adder::AdderReply reply;

		// Context for the client. It could be used to convey extra information to
		// the server and/or tweak certain RPC behaviors.
		grpc::ClientContext context;

		// The actual RPC.
		grpc::Status status = stub_->Add(&context, request, &reply);

		// Act upon its status.
		if (status.ok()) 
		{
			return reply.sum();
		} 
		else {
			std::cout << "RPC failed" << std::endl;
			return -1;
		}
	}

private:
	std::unique_ptr<adder::Adder::Stub> stub_;
};

int main(int argc, char** argv) {
	// Instantiate the client. It requires a channel, out of which the actual RPCs
	// are created. This channel models a connection to an endpoint (in this case,
	// localhost at port 50051). We indicate that the channel isn't authenticated
	// (use of InsecureChannelCredentials()).
	AdderClient adder(grpc::CreateChannel("localhost:50051",
										  grpc::InsecureChannelCredentials()));
	int a = 5;
	int b = 7;
	int sum = adder.Add(a, b);
	std::cout << "Adder received: " << sum << std::endl;

	return 0;
}