#include <algorithm>
#include <cassert>

#include <glm/gtc/type_ptr.hpp>

#include "framebuffer.h"

namespace cardinal {
namespace rendering {

Framebuffer::Framebuffer(int outputs, const glm::ivec2 dimension, int samples, bool depth) {
    assert(outputs > 0 && outputs <= 32);
    output_textures_.resize(outputs);
    depth_ = depth;
    Resize(dimension, samples);
}

Framebuffer::Framebuffer(Framebuffer &&other) {
    output_textures_ = std::move(other.output_textures_);
    depth_texture_ = other.depth_texture_;
    other.depth_texture_ = 0;
    framebuffer_ = other.framebuffer_;
    other.framebuffer_ = 0;
    samples_ = other.samples_;
    other.samples_ = 0;
    dimension_ = other.dimension_;
}

Framebuffer::~Framebuffer() { Destroy(); }

void Framebuffer::operator=(Framebuffer &&other) {
    Destroy();
    output_textures_ = std::move(other.output_textures_);
    depth_texture_ = other.depth_texture_;
    other.depth_texture_ = 0;
    framebuffer_ = other.framebuffer_;
    other.framebuffer_ = 0;
    samples_ = other.samples_;
    other.samples_ = 0;
    dimension_ = other.dimension_;
}

void Framebuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_); }

void Framebuffer::Clear(int index, const glm::vec4 &color) const {
    assert(index >= 0 && index < static_cast<int>(output_textures_.size()));
    Bind();
    glClearBufferfv(GL_COLOR, index, glm::value_ptr(color));
}

void Framebuffer::ClearDepth() const {
    Bind();
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::Resize(const glm::ivec2 dimension, int samples) {
    Destroy();
    dimension_ = dimension;
    samples_ = samples;
    assert(dimension_.x > 0 && dimension_.y > 0 && samples_ > 0);
    Create();
}

void Framebuffer::BlitToScreen(int index, const glm::ivec2 dimension) const {
    assert(index >= 0 && index < static_cast<int>(output_textures_.size()));

    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
    glBlitFramebuffer(0, 0, dimension_.x, dimension_.y, 0, 0, dimension.x, dimension.y, GL_COLOR_BUFFER_BIT,
                      GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BlitTo(int index, const Framebuffer &other) const {
    assert(index >= 0 && index < static_cast<int>(output_textures_.size()));

    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, other.framebuffer_);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
    glBlitFramebuffer(0, 0, dimension_.x, dimension_.y, 0, 0, other.dimension_.x, other.dimension_.y,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Create() {
    GLenum type = samples_ == 1 ? GL_TEXTURE_2D : GL_TEXTURE_2D_MULTISAMPLE;
    std::vector<GLenum> draw_buffers;

    glCreateFramebuffers(1, &framebuffer_);
    glCreateTextures(type, output_textures_.size(), output_textures_.data());

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
    for (int i = 0, n = static_cast<int>(output_textures_.size()); i < n; i++) {
        if (samples_ == 1) {
            glTextureStorage2D(output_textures_[i], 1, GL_RGBA8, dimension_.x, dimension_.y);
            glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        } else {
            glTextureStorage2DMultisample(output_textures_[i], samples_, GL_RGBA8, dimension_.x, dimension_.y, GL_TRUE);
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, type, output_textures_[i], 0);
        draw_buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
    }
    if (depth_) {
        glCreateTextures(type, 1, &depth_texture_);
        if (samples_ == 1) {
            glTextureStorage2D(depth_texture_, 0, GL_DEPTH_COMPONENT32, dimension_.x, dimension_.y);
            glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        } else {
            glTextureStorage2DMultisample(depth_texture_, samples_, GL_DEPTH_COMPONENT32, dimension_.x, dimension_.y,
                                          GL_TRUE);
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, type, depth_texture_, 0);
    }
    glDrawBuffers(draw_buffers.size(), draw_buffers.data());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Destroy() {
    glDeleteTextures(output_textures_.size(), output_textures_.data());
    glDeleteTextures(1, &depth_texture_);
    glDeleteFramebuffers(1, &framebuffer_);
    depth_texture_ = framebuffer_ = 0;
}

} // namespace rendering
} // namespace cardinal