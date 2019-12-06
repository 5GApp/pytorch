#include <torch/csrc/distributed/rpc/rpc_agent.h>

namespace torch {
namespace distributed {
namespace rpc {

constexpr size_t WorkerInfo::MAX_NAME_LEN;

RpcAgent::RpcAgent(
    WorkerInfo workerId,
    std::unique_ptr<RequestCallback> cb,
    std::chrono::milliseconds rpcTimeout)
    : workerInfo_(std::move(workerId)),
      cb_(std::move(cb)),
      rpcTimeout_(rpcTimeout) {}

RpcAgent::~RpcAgent() = default;

const WorkerInfo& RpcAgent::getWorkerInfo() const {
  return workerInfo_;
}

std::shared_ptr<RpcAgent> RpcAgent::defaultRpcAgent_ = nullptr;

std::shared_ptr<RpcAgent> RpcAgent::getDefaultRpcAgent() {
  TORCH_INTERNAL_ASSERT(
      defaultRpcAgent_, "Default rpc agent is not initialized!");
  return defaultRpcAgent_;
}

void RpcAgent::setDefaultRpcAgent(std::shared_ptr<RpcAgent> defaultRpcAgent) {
  TORCH_INTERNAL_ASSERT(
      !defaultRpcAgent_, "Default rpc agent is already initialized!");
  defaultRpcAgent_ = std::move(defaultRpcAgent);
}

std::unordered_map<std::string, std::string> RpcAgent::getMetrics() {
  std::unordered_map<std::string, std::string> metrics;
  // Default implementation: return empty map.
  return metrics;
}

std::unordered_map<std::string, std::string> RpcAgent::getDebugInfo() {
  /* This would later include more info other than metrics for eg: may include
     stack traces for the threads owned by the agent */
  // Default implementation: return getMetrics().
  return getMetrics();
}

void RpcAgent::addGilWaitTime(
    const std::chrono::microseconds gilWaitTime /* unused */) {
  // No-op default implementation
}

} // namespace rpc
} // namespace distributed
} // namespace torch
