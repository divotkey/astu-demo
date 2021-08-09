/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

// Local includes
#include "EditorService.h"

// C++ Standard Library includes
#include <cassert>
#include <iostream>

using namespace astu2d;
using namespace astu;
using namespace std;

#define GRID_WIDTH  2
#define GRID_HEIGHT 3
#define GRID_STEP   0.25f
#define DOT_RADIUS  0.05f
#define EPSILON     DOT_RADIUS

EditorService::EditorService()
    : BaseService("Editor Service")
    , mode(Mode::Polygon)
{
    // Intentionally left empty.    
}

void EditorService::OnStartup()
{
    auto node = NodeBuilder()
        .Name("Grid")
        .AttachChild(PolylineBuilder()
            .Color(RalColors::TrafficGreyA)
            .VertexBuffer(ShapeGenerator().GenRectangle(GRID_WIDTH, GRID_HEIGHT))
            .Build())
        .Build();

    int n = static_cast<int>(GRID_HEIGHT / GRID_STEP);
    float d = GRID_HEIGHT / static_cast<float>(n);
    for (int i = 1; i < n; ++i) {
        node->AttachChild(PolylineBuilder()
            .Color(RalColors::TrafficGreyB)
            .VertexBuffer(ShapeGenerator()
                .GenLine(
                    -GRID_WIDTH / 2.0f, 
                    -GRID_HEIGHT / 2.0f + i * d, 
                    GRID_WIDTH / 2.0f, 
                    -GRID_HEIGHT / 2.0f + i * d))
            .Build());
    }

    n = static_cast<int>(GRID_WIDTH / GRID_STEP);
    d = GRID_WIDTH / static_cast<float>(n);
    for (int i = 1; i < n; ++i) {
        node->AttachChild(PolylineBuilder()
            .Color(RalColors::TrafficGreyB)
            .VertexBuffer(ShapeGenerator()
                .GenLine(
                    -GRID_WIDTH / 2.0f + i * d, 
                    -GRID_HEIGHT / 2.0f, 
                    -GRID_WIDTH / 2.0f + i * d, 
                    GRID_HEIGHT / 2.0f))
            .Build());
    }

    ASTU_SERVICE(SceneGraph).GetRoot()->AttachChild(node);
}

void EditorService::OnShutdown()
{    
    ASTU_SERVICE(SceneGraph).GetRoot()->DetachChild("Grid");   
}

bool EditorService::OnMouseButtonPressed(int button, int x, int y)
{
    if (button != Mouse::Button::LEFT) {
        return false;
    }
    auto wp = GetCamera().GetInverseMatrix().TransformPoint((float) x, float (y));
    wp.x = MathUtils::Snap(wp.x, GRID_STEP);
    wp.y = MathUtils::Snap(wp.y, GRID_STEP);

    switch (mode) {

    case Mode::Polygon:
        vertices.push_back(wp);
        break;

    case Mode::Dots:
        vertices.push_back(wp);
        break;

    case Mode::Lines: {
            uint32_t idx;
            if (!FindVertex(wp, idx)) {
                break;
            }

            if (point1.has_value()) {
                indices.push_back(*point1);
                indices.push_back(idx);
                point1.reset();
            } else {
                point1 = idx;
            }
            break;
        }
    }
    
    return true;
}

bool EditorService::OnKeyPressed(int keycode)
{
    switch(keycode) {

    case Keyboard::KEY_DELETE:
        vertices.clear();
        indices.clear();
        point1.reset();
        return true;

    case Keyboard::KEY_BACKSPACE:
        switch (mode) {
            case Mode::Polygon:
            case Mode::Dots:
                if (!vertices.empty()) {
                    vertices.pop_back();
                }
                break;

            case Mode::Lines:
                assert(indices.size() % 2 == 0);
                if (!indices.empty()) {
                    indices.pop_back();
                    indices.pop_back();
                }
                break;
        }
        return true;

    case Keyboard::KEY_RETURN:
        switch (mode) {
            case Mode::Polygon:
            case Mode::Dots:
                EmitVertices();
                break;

            case Mode::Lines:
                EmitLines();
                break;
        }
        return true;

    case Keyboard::KEY_F1:
        mode = Mode::Polygon;
        cout << "switch to polyon mode" << endl;
        return true;

    case Keyboard::KEY_F2:
        mode = Mode::Dots;
        cout << "switch to vertex mode" << endl;
        return true;

    case Keyboard::KEY_F3:
        mode = Mode::Lines;
        cout << "switch to line mode" << endl;
        return true;
    }

    return false;
}

void EditorService::OnUpdate()
{
    SetViewTransform(GetCamera().GetMatrix());
    SetDrawColor(RalColors::TrafficYellow);

    switch (mode) {

    case Mode::Polygon:
        DrawLines(vertices);
        break;

    case Mode::Dots:
        for (const auto& vertex : vertices) {
            DrawDot(vertex);
        }
        break;

    case Mode::Lines:
        for (const auto& vertex : vertices) {
            DrawDot(vertex);
        }
        assert(indices.size() % 2 == 0);
        for (auto it = indices.begin(); it != indices.end();) {
            const auto& p1 = vertices[*it++];
            const auto& p2 = vertices[*it++];
            DrawLine(p1, p2);
        }
        break;
    }
}

void EditorService::DrawDot(const astu::Vector2f& p)
{
    DrawCircle(p, DOT_RADIUS);
}

bool EditorService::FindVertex(const astu::Vector2f& p, uint32_t& outIdx) const
{
    uint32_t idx = 0;
    for (const auto& vertex : vertices) {
        if (vertex.Distance(p) < EPSILON) {
            outIdx = idx;
            return true;
        }
        ++idx;
    }
    return false;
}

void EditorService::EmitVertices()
{
    cout << "vertices = [";
    for (size_t i = 0; i < vertices.size(); ++i) {
        cout << "[" << vertices[i].x << ", " << vertices[i].y << "]";
        if (i < vertices.size() - 1) {
            cout << ", ";
        }
    }
    cout << "];" << endl;
}

void EditorService::EmitLines()
{
    cout << "AddChar(" << endl << "\"?\", " << endl << "[";
    for (size_t i = 0; i < vertices.size(); ++i) {
        cout << "[" << vertices[i].x << ", " << vertices[i].y << "]";
        if (i < vertices.size() - 1) {
            cout << ", ";
        }
    }
    cout << "], " << endl << "[";

    for (size_t i = 0; i < indices.size(); ++i) {
        cout << indices[i];
        if (i < indices.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]," << endl << "fontScale" << endl << ");" << endl;

}