#include <mcap/mcap.hpp>

#include <benchmark/benchmark.h>

#include <array>
#include <cstdio>
#include <cstring>
#include <fstream>

constexpr char StringSchema[] = "string data";
constexpr size_t WriteIterations = 10000;

static void BM_McapWriterBufferedWriterUnchunkedUnindexed(benchmark::State& state) {
  // Create a message payload
  std::array<std::byte, 4 + 13> payload;
  const uint32_t length = 13;
  std::memcpy(payload.data(), &length, 4);
  std::memcpy(payload.data() + 4, "Hello, world!", 13);

  // Create an unchunked writer using the ros1 profile
  mcap::McapWriter writer;
  auto options = mcap::McapWriterOptions("ros1");
  options.noChunking = true;
  options.noIndexing = true;

  // Open an output memory buffer and write the file header
  mcap::BufferedWriter out{};
  writer.open(out, options);

  // Register a Channel Info record
  mcap::ChannelInfo topic("/chatter", "ros1", "std_msgs/String", StringSchema);
  writer.addChannel(topic);

  // Create a message
  mcap::Message msg;
  msg.channelId = topic.channelId;
  msg.sequence = 0;
  msg.publishTime = 0;
  msg.recordTime = msg.publishTime;
  msg.data = payload.data();
  msg.dataSize = payload.size();

  while (state.KeepRunning()) {
    for (size_t i = 0; i < WriteIterations; i++) {
      writer.write(msg);
      benchmark::ClobberMemory();
    }
  }

  // Finish writing the file to memory
  writer.close();
}

static void BM_McapWriterBufferedWriterUnchunked(benchmark::State& state) {
  // Create a message payload
  std::array<std::byte, 4 + 13> payload;
  const uint32_t length = 13;
  std::memcpy(payload.data(), &length, 4);
  std::memcpy(payload.data() + 4, "Hello, world!", 13);

  // Create an unchunked writer using the ros1 profile
  mcap::McapWriter writer;
  auto options = mcap::McapWriterOptions("ros1");
  options.noChunking = true;

  // Open an output memory buffer and write the file header
  mcap::BufferedWriter out{};
  writer.open(out, options);

  // Register a Channel Info record
  mcap::ChannelInfo topic("/chatter", "ros1", "std_msgs/String", StringSchema);
  writer.addChannel(topic);

  // Create a message
  mcap::Message msg;
  msg.channelId = topic.channelId;
  msg.sequence = 0;
  msg.publishTime = 0;
  msg.recordTime = msg.publishTime;
  msg.data = payload.data();
  msg.dataSize = payload.size();

  while (state.KeepRunning()) {
    for (size_t i = 0; i < WriteIterations; i++) {
      writer.write(msg);
      benchmark::ClobberMemory();
    }
  }

  // Finish writing the file to memory
  writer.close();
}

static void BM_McapWriterBufferedWriterChunked(benchmark::State& state) {
  // Create a message payload
  std::array<std::byte, 4 + 13> payload;
  const uint32_t length = 13;
  std::memcpy(payload.data(), &length, 4);
  std::memcpy(payload.data() + 4, "Hello, world!", 13);

  // Create a chunked writer using the ros1 profile
  mcap::McapWriter writer;
  auto options = mcap::McapWriterOptions("ros1");
  options.chunkSize = uint64_t(state.range(0));

  // Open an output memory buffer and write the file header
  mcap::BufferedWriter out{};
  writer.open(out, options);

  // Register a Channel Info record
  mcap::ChannelInfo topic("/chatter", "ros1", "std_msgs/String", StringSchema);
  writer.addChannel(topic);

  // Create a message
  mcap::Message msg;
  msg.channelId = topic.channelId;
  msg.sequence = 0;
  msg.publishTime = 0;
  msg.recordTime = msg.publishTime;
  msg.data = payload.data();
  msg.dataSize = payload.size();

  while (state.KeepRunning()) {
    for (size_t i = 0; i < WriteIterations; i++) {
      writer.write(msg);
      benchmark::ClobberMemory();
    }
  }

  // Finish writing the file to memory
  writer.close();
}

static void BM_McapWriterBufferedWriterChunkedUnindexed(benchmark::State& state) {
  // Create a message payload
  std::array<std::byte, 4 + 13> payload;
  const uint32_t length = 13;
  std::memcpy(payload.data(), &length, 4);
  std::memcpy(payload.data() + 4, "Hello, world!", 13);

  // Create a chunked writer using the ros1 profile
  mcap::McapWriter writer;
  auto options = mcap::McapWriterOptions("ros1");
  options.noIndexing = true;
  options.chunkSize = uint64_t(state.range(0));

  // Open an output memory buffer and write the file header
  mcap::BufferedWriter out{};
  writer.open(out, options);

  // Register a Channel Info record
  mcap::ChannelInfo topic("/chatter", "ros1", "std_msgs/String", StringSchema);
  writer.addChannel(topic);

  // Create a message
  mcap::Message msg;
  msg.channelId = topic.channelId;
  msg.sequence = 0;
  msg.publishTime = 0;
  msg.recordTime = msg.publishTime;
  msg.data = payload.data();
  msg.dataSize = payload.size();

  while (state.KeepRunning()) {
    for (size_t i = 0; i < WriteIterations; i++) {
      writer.write(msg);
      benchmark::ClobberMemory();
    }
  }

  // Finish writing the file to memory
  writer.close();
}

static void BM_McapWriterBufferedWriterLZ4(benchmark::State& state) {
  // Create a message payload
  std::array<std::byte, 4 + 13> payload;
  const uint32_t length = 13;
  std::memcpy(payload.data(), &length, 4);
  std::memcpy(payload.data() + 4, "Hello, world!", 13);

  // Create a chunked writer using the ros1 profile
  mcap::McapWriter writer;
  auto options = mcap::McapWriterOptions("ros1");
  options.chunkSize = uint64_t(state.range(0));
  options.compression = mcap::Compression::Lz4;
  options.compressionLevel = mcap::CompressionLevel(state.range(1));

  // Open an output memory buffer and write the file header
  mcap::BufferedWriter out{};
  writer.open(out, options);

  // Register a Channel Info record
  mcap::ChannelInfo topic("/chatter", "ros1", "std_msgs/String", StringSchema);
  writer.addChannel(topic);

  // Create a message
  mcap::Message msg;
  msg.channelId = topic.channelId;
  msg.sequence = 0;
  msg.publishTime = 0;
  msg.recordTime = msg.publishTime;
  msg.data = payload.data();
  msg.dataSize = payload.size();

  while (state.KeepRunning()) {
    for (size_t i = 0; i < WriteIterations; i++) {
      writer.write(msg);
      benchmark::ClobberMemory();
    }
  }

  // Finish writing the file to memory
  writer.close();
}

static void BM_McapWriterBufferedWriterZStd(benchmark::State& state) {
  // Create a message payload
  std::array<std::byte, 4 + 13> payload;
  const uint32_t length = 13;
  std::memcpy(payload.data(), &length, 4);
  std::memcpy(payload.data() + 4, "Hello, world!", 13);

  // Create a chunked writer using the ros1 profile
  mcap::McapWriter writer;
  auto options = mcap::McapWriterOptions("ros1");
  options.chunkSize = uint64_t(state.range(0));
  options.compression = mcap::Compression::Zstd;
  options.compressionLevel = mcap::CompressionLevel(state.range(1));

  // Open an output memory buffer and write the file header
  mcap::BufferedWriter out{};
  writer.open(out, options);

  // Register a Channel Info record
  mcap::ChannelInfo topic("/chatter", "ros1", "std_msgs/String", StringSchema);
  writer.addChannel(topic);

  // Create a message
  mcap::Message msg;
  msg.channelId = topic.channelId;
  msg.sequence = 0;
  msg.publishTime = 0;
  msg.recordTime = msg.publishTime;
  msg.data = payload.data();
  msg.dataSize = payload.size();

  while (state.KeepRunning()) {
    for (size_t i = 0; i < WriteIterations; i++) {
      writer.write(msg);
      benchmark::ClobberMemory();
    }
  }

  // Finish writing the file to memory
  writer.close();
}

static void BM_McapWriterStreamWriterUnchunked(benchmark::State& state) {
  // Create a message payload
  std::array<std::byte, 4 + 13> payload;
  const uint32_t length = 13;
  std::memcpy(payload.data(), &length, 4);
  std::memcpy(payload.data() + 4, "Hello, world!", 13);

  // Create an unchunked writer using the ros1 profile
  mcap::McapWriter writer;
  auto options = mcap::McapWriterOptions("ros1");
  options.noChunking = true;

  // Open an output file stream and write the file header
  std::ofstream out("benchmark.mcap", std::ios::binary);
  writer.open(out, options);

  // Register a Channel Info record
  mcap::ChannelInfo topic("/chatter", "ros1", "std_msgs/String", StringSchema);
  writer.addChannel(topic);

  // Create a message
  mcap::Message msg;
  msg.channelId = topic.channelId;
  msg.sequence = 0;
  msg.publishTime = 0;
  msg.recordTime = msg.publishTime;
  msg.data = payload.data();
  msg.dataSize = payload.size();

  while (state.KeepRunning()) {
    for (size_t i = 0; i < WriteIterations; i++) {
      writer.write(msg);
      benchmark::ClobberMemory();
    }
  }

  // Finish writing the file and delete it
  writer.close();
  std::remove("benchmark.mcap");
}

static void BM_McapWriterStreamWriterChunked(benchmark::State& state) {
  // Create a message payload
  std::array<std::byte, 4 + 13> payload;
  const uint32_t length = 13;
  std::memcpy(payload.data(), &length, 4);
  std::memcpy(payload.data() + 4, "Hello, world!", 13);

  // Create a chunked writer using the ros1 profile
  mcap::McapWriter writer;
  auto options = mcap::McapWriterOptions("ros1");
  options.chunkSize = uint64_t(state.range(0));

  // Open an output file stream and write the file header
  std::ofstream out("benchmark.mcap", std::ios::binary);
  writer.open(out, options);

  // Register a Channel Info record
  mcap::ChannelInfo topic("/chatter", "ros1", "std_msgs/String", StringSchema);
  writer.addChannel(topic);

  // Create a message
  mcap::Message msg;
  msg.channelId = topic.channelId;
  msg.sequence = 0;
  msg.publishTime = 0;
  msg.recordTime = msg.publishTime;
  msg.data = payload.data();
  msg.dataSize = payload.size();

  while (state.KeepRunning()) {
    for (size_t i = 0; i < WriteIterations; i++) {
      writer.write(msg);
      benchmark::ClobberMemory();
    }
  }

  // Finish writing the file and delete it
  writer.close();
  std::remove("benchmark.mcap");
}

int main(int argc, char* argv[]) {
  benchmark::RegisterBenchmark("BM_McapWriterBufferedWriterUnchunkedUnindexed",
                               BM_McapWriterBufferedWriterUnchunkedUnindexed);
  benchmark::RegisterBenchmark("BM_McapWriterBufferedWriterUnchunked",
                               BM_McapWriterBufferedWriterUnchunked);
  benchmark::RegisterBenchmark("BM_McapWriterBufferedWriterChunked",
                               BM_McapWriterBufferedWriterChunked)
    ->Arg(1)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000)
    ->Arg(100000)
    ->Arg(1000000)
    ->Arg(10000000);
  benchmark::RegisterBenchmark("BM_McapWriterBufferedWriterChunkedUnindexed",
                               BM_McapWriterBufferedWriterChunkedUnindexed)
    ->Arg(1)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000)
    ->Arg(100000)
    ->Arg(1000000)
    ->Arg(10000000);
  benchmark::RegisterBenchmark("BM_McapWriterBufferedWriterLZ4", BM_McapWriterBufferedWriterLZ4)
    ->Args({1, 0})
    ->Args({1, 1})
    ->Args({1, 2})
    ->Args({100000, 0})
    ->Args({100000, 1})
    ->Args({100000, 2});
  benchmark::RegisterBenchmark("BM_McapWriterBufferedWriterZStd", BM_McapWriterBufferedWriterZStd)
    ->Args({1, 0})
    ->Args({1, 1})
    ->Args({1, 2})
    ->Args({1, 3})
    ->Args({1, 4})
    ->Args({100000, 0})
    ->Args({100000, 1})
    ->Args({100000, 2})
    ->Args({100000, 3})
    ->Args({100000, 4});
  benchmark::RegisterBenchmark("BM_McapWriterStreamWriterUnchunked",
                               BM_McapWriterStreamWriterUnchunked);
  benchmark::RegisterBenchmark("BM_McapWriterStreamWriterChunked", BM_McapWriterStreamWriterChunked)
    ->Arg(1)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000)
    ->Arg(100000)
    ->Arg(1000000)
    ->Arg(10000000);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}