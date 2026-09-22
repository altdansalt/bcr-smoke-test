// Constructs a google::rpc::Status (from @googleapis//google/rpc:status_cc_proto,
// which is a real cc_proto_library only because googleapis-cc is a bazel_dep)
// and round-trips it inside a local message.
#include "google/longrunning/operations.grpc.pb.h"
#include "google/rpc/status.pb.h"
#include "grpcpp/grpcpp.h"
#include "gtest/gtest.h"
#include "proto/googleapis/result.pb.h"

TEST(Googleapis, RpcStatusAndTypeDate) {
  google::rpc::Status status;
  status.set_code(5);  // NOT_FOUND
  status.set_message("nope");

  smoke::googleapis::Result in;
  *in.mutable_status() = status;
  in.mutable_when()->set_year(2026);
  in.mutable_when()->set_month(9);
  in.mutable_when()->set_day(22);

  smoke::googleapis::Result out;
  ASSERT_TRUE(out.ParseFromString(in.SerializeAsString()));
  EXPECT_EQ(out.status().code(), 5);
  EXPECT_EQ(out.status().message(), "nope");
  EXPECT_EQ(out.when().year(), 2026);
}

// googleapis-grpc-cc: the generated Operations stub links and can be created
// (no connection is attempted).
TEST(Googleapis, LongrunningGrpcStubLinks) {
  auto channel = ::grpc::CreateChannel("127.0.0.1:1",
                                       ::grpc::InsecureChannelCredentials());
  auto stub = google::longrunning::Operations::NewStub(channel);
  EXPECT_NE(stub, nullptr);
}
