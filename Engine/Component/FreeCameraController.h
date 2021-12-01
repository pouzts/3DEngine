#pragma once
#include "Component.h"

namespace PhoenixEngine
{
    class FreeCameraController : public Component
    {
    public:
        void Update() override;

        virtual bool Write(const rapidjson::Value& value) const override;
        virtual bool Read(const rapidjson::Value& value) override;

    public:
        float speed{ 1 };
        float sensitivity{ 1 };
    };
}