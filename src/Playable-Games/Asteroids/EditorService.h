/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// AST-Utilities includes
#include <AstuServices.h>
#include <AstuSuite2D.h>

// C++ Standard Library includes
#include <cstdint>
#include <optional>

class EditorService 
    : public astu::BaseService
    , private astu2d::LineRendererClient2f
    , private astu2d::CameraClient
    , private astu::MouseButtonListener
    , private astu::KeystrokeListener
    , private astu::Updatable
{
public:
    // Constructor.
    EditorService();

private:
    enum class Mode {Polygon, Dots, Lines};

    /** The mode, this editor is currently operating. */
    Mode mode;

    /** The vertices added by the user. */
    std::vector<astu::Vector2f> vertices;

    /** The lines added by the user. */
    std::vector<uint32_t> indices;

    /** The first point of the line. */
    std::optional<uint32_t> point1;

    void EmitVertices();
    void EmitLines();
    void DrawDot(const astu::Vector2f& p);
    bool FindVertex(const astu::Vector2f& p, uint32_t& outIdx) const;

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via MouseButtonListener
    virtual bool OnMouseButtonPressed(int button, int x, int y) override;

    // Inherited via KeystrokeListener
    virtual bool OnKeyPressed(int keycode) override;

    // Inherited via Updatable
    virtual void OnUpdate() override;
 };