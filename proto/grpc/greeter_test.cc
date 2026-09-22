// Starts an insecure gRPC server on a free localhost port in-process and makes
// one unary RPC through a real channel.
#include <memory>
#include <string>

#include "grpcpp/grpcpp.h"
#include "gtest/gtest.h"
#include "proto/grpc/greeter.grpc.pb.h"
#include "proto/grpc/greeter.pb.h"

namespace {

class GreeterImpl final : public smoke::grpc::Greeter::Service {
  ::grpc::Status SayHello(::grpc::ServerContext*,
                          const smoke::grpc::HelloRequest* req,
                          smoke::grpc::HelloReply* reply) override {
    reply->set_message("Hello " + req->name());
    return ::grpc::Status::OK;
  }
};

TEST(Greeter, UnaryRpcOverLocalhost) {
  GreeterImpl service;
  int port = 0;
  ::grpc::ServerBuilder builder;
  builder.AddListeningPort("127.0.0.1:0", ::grpc::InsecureServerCredentials(),
                           &port);
  builder.RegisterService(&service);
  std::unique_ptr<::grpc::Server> server = builder.BuildAndStart();
  ASSERT_NE(server, nullptr);
  ASSERT_GT(port, 0);

  auto channel = ::grpc::CreateChannel("127.0.0.1:" + std::to_string(port),
                                       ::grpc::InsecureChannelCredentials());
  auto stub = smoke::grpc::Greeter::NewStub(channel);

  smoke::grpc::HelloRequest req;
  req.set_name("bazel");
  smoke::grpc::HelloReply reply;
  ::grpc::ClientContext ctx;
  ::grpc::Status status = stub->SayHello(&ctx, req, &reply);
  ASSERT_TRUE(status.ok()) << status.error_message();
  EXPECT_EQ(reply.message(), "Hello bazel");

  server->Shutdown();
}

}  // namespace
