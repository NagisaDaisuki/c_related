// Copyright 2026 MyProject Authors. All Rights Reserved.
// 文件名：google_cpp_style.cpp
// 说明：演示 Google C++ Style 的主要规则。

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 命名空间：全部小写，用下划线分隔，禁止缩写
namespace my_project {
namespace audio_video {

// 常量：k 开头 + CamelCase
constexpr int kMaxFrameCount = 100;
constexpr double kDefaultSampleRate = 44100.0;

// 枚举：CamelCase，枚举值 k 开头 + CamelCase
enum class CodecType {
  kH264,
  kH265,
  kAV1,
};

// 结构体：CamelCase，成员小写+下划线
struct VideoFrame {
  int width = 0;
  int height = 0;
  double pts = 0.0;
  std::vector<uint8_t> data;
};

// 类：CamelCase，成员变量小写+下划线+末尾下划线
class VideoDecoder {
public:
  // 构造函数：CamelCase
  explicit VideoDecoder(CodecType codec) : codec_(codec) {}
  // 析构函数：CamelCase
  ~VideoDecoder() = default;

  // 禁止拷贝：Google Style 推荐用  = delete;
  VideoDecoder(const VideoDecoder &) = delete;
  VideoDecoder &operator=(const VideoDecoder &) = delete;

  // 普通函数：CamelCase
  bool Open(const std::string &filename) {
    filename_ = filename;
    return true;
  }

  // 返回值用 bool，输出参数用指针
  bool DecodeFrame(VideoFrame *out_frame) {
    if (out_frame == nullptr) {
      return false;
    }
    out_frame->width = 1920;
    out_frame->height = 1080;
    out_frame->pts = 0.0;
    return true;
  }

  // 只读访问器：小写+下划线
  CodecType codec() const { return codec_; }

private:
  CodecType codec_;
  std::string filename_;
};

// 函数：CamelCase，参数小写+下划线
double CalculateDuration(double pts, double time_base) {
  return pts * time_base;
}

// 函数注释用 //, 不要用 /* */
// 返回解码器名称，空字符表示未知
std::string GetCodecName(CodecType codec) {
  switch (codec) {
  case CodecType::kH264:
    return "H.264";
  case CodecType::kH265:
    return "H.265";
  case CodecType::kAV1:
    return "AV1";
  default:
    return "";
  }
}
} // namespace audio_video
} // namespace my_project

int main(int argc, char **argv) {
  using my_project::audio_video::CodecType;
  using my_project::audio_video::GetCodecName;
  using my_project::audio_video::VideoDecoder;
  using my_project::audio_video::VideoFrame;

  // 局部变量：小写+下划线
  auto decoder = std::make_unique<VideoDecoder>(CodecType::kH264);

  if (!decoder->Open("test.mp4")) {
    std::cerr << "Failed to open file." << std::endl;
    return 1;
  }

  VideoFrame frame;

  if (decoder->DecodeFrame(&frame)) {
    std::cout << "Codec: " << GetCodecName(decoder->codec()) << std::endl;
    std::cout << "Resolution: " << frame.width << "x" << frame.height
              << std::endl;
  }

  return 0;
}
