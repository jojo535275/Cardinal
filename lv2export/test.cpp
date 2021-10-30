/*
 * DISTRHO Cardinal Plugin
 * Copyright (C) 2021 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the LICENSE file.
 */

#include <rack.hpp>
#include <context.hpp>

#include "DistrhoUtils.hpp"

using namespace rack;

extern Model* modelSpringReverb;
Plugin* pluginInstance__Befaco;

namespace rack {
Context::~Context() {
}
static thread_local Context* threadContext = nullptr;
Context* contextGet() {
	DISTRHO_SAFE_ASSERT(threadContext != nullptr);
	return threadContext;
}
// Apple's clang incorrectly compiles this function when -O2 or higher is enabled.
#ifdef ARCH_MAC
__attribute__((optnone))
#endif
void contextSet(Context* const context) {
	// DISTRHO_SAFE_ASSERT(threadContext == nullptr);
	threadContext = context;
}
Exception::Exception(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    msg = string::fV(format, args);
    va_end(args);
}
namespace asset {
std::string plugin(plugin::Plugin* plugin, std::string filename) { return {}; }
std::string system(std::string filename) { return {}; }
}
namespace engine {
float Engine::getParamValue(Module* module, int paramId) { return 0.0f; }
float Engine::getParamSmoothValue(Module* module, int paramId) { return 0.0f; }
void Engine::setParamValue(Module* module, int paramId, float value) {}
void Engine::setParamSmoothValue(Module* module, int paramId, float value) {}
}
namespace plugin {
void Plugin::addModel(Model* model)
{
	// Check that the model is not added to a plugin already
    DISTRHO_SAFE_ASSERT_RETURN(model != nullptr,);
	DISTRHO_SAFE_ASSERT_RETURN(model->plugin == nullptr,);
	model->plugin = this;
	models.push_back(model);
}
Model* modelFromJson(json_t* moduleJ) {
    return nullptr;
}
std::vector<Plugin*> plugins;
} // namespace plugin
} // namespace rack

int main()
{
    Plugin* const p = new Plugin;
    pluginInstance__Befaco = p;
    p->addModel(modelSpringReverb);

    d_stdout("modelSpringReverb is %p", modelSpringReverb);
    return 0;
}
