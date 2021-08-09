/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 *
 * Code generated with SWORD 1.8.15
 * Last modified: Thu Aug 05 19:18:45 CEST 2021
 */

// Local includes
#include "MeshData.h"

using namespace astu;
using namespace std;

/////////////////////////////////////////////////
/////// Asteroids Data
/////////////////////////////////////////////////

const std::array<MeshData, 4> kBigAsteroids = {
	MeshData(
		// Name
		"AsteroidBig1",
	
		// Radius
		3.577708763999664f, 
	
		// 10 Vertices
		{{2.4f, 0.0f}, {3.2f, -1.6f}, {1.6f, -3.2f}, {0.0f, -1.6f}, 
		{-1.6f, -3.2f}, {-3.2f, -1.6f}, {-3.2f, 1.6f}, {-1.6f, 3.2f}, 
		{0.8f, 3.2f}, {3.2f, 1.6f}}
	),
	
	MeshData(
		// Name
		"AsteroidBig2",
	
		// Radius
		3.577708763999664f, 
	
		// 12 Vertices
		{{3.2f, 0.8f}, {1.6f, -0.8f}, {3.2f, -1.6f}, {1.6f, -3.2f}, 
		{0.0f, -2.4f}, {-1.6f, -3.2f}, {-3.2f, -1.6f}, {-2.4f, 0.0f}, 
		{-3.2f, 1.6f}, {-1.6f, 3.2f}, {-0.8f, 2.4f}, {1.6f, 3.2f}
		}
	),
	
	MeshData(
		// Name
		"AsteroidBig3",
	
		// Radius
		3.298484500494129f, 
	
		// 11 Vertices
		{{3.2f, 0.8f}, {3.2f, -0.8f}, {1.6f, -3.2f}, {-0.8f, -3.2f}, 
		{-3.2f, -0.8f}, {-1.6f, -0.8f}, {-3.2f, 0.8f}, {-1.6f, 3.2f}, 
		{0.0f, 0.8f}, {0.0f, 3.2f}, {1.6f, 3.2f}}
	),
	
	MeshData(
		// Name
		"AsteroidBig4",
	
		// Radius
		3.577708763999664f, 
	
		// 12 Vertices
		{{0.8f, 0.0f}, {3.2f, -0.8f}, {3.2f, -1.6f}, {0.8f, -3.2f}, 
		{-1.6f, -3.2f}, {-0.8f, -1.6f}, {-3.2f, -1.6f}, {-3.2f, 0.8f}, 
		{-1.6f, 3.2f}, {0.8f, 2.4f}, {1.6f, 3.2f}, {3.2f, 1.6f}
		}
	)
};

const std::array<MeshData, 4> kMediumAsteroids = {
	MeshData(
		// Name
		"AsteroidMedium1",
	
		// Radius
		2.2181794336797913f, 
	
		// 10 Vertices
		{{1.488f, 0.0f}, {1.984f, -0.992f}, {0.992f, -1.984f}, {0.0f, -0.992f}, 
		{-0.992f, -1.984f}, {-1.984f, -0.992f}, {-1.984f, 0.992f}, {-0.992f, 1.984f}, 
		{0.496f, 1.984f}, {1.984f, 0.992f}}
	),
	
	MeshData(
		// Name
		"AsteroidMedium2",
	
		// Radius
		2.2181794336797913f, 
	
		// 12 Vertices
		{{1.984f, 0.496f}, {0.992f, -0.496f}, {1.984f, -0.992f}, {0.992f, -1.984f}, 
		{0.0f, -1.488f}, {-0.992f, -1.984f}, {-1.984f, -0.992f}, {-1.488f, 0.0f}, 
		{-1.984f, 0.992f}, {-0.992f, 1.984f}, {-0.496f, 1.488f}, {0.992f, 1.984f}
		}
	),
	
	MeshData(
		// Name
		"AsteroidMedium3",
	
		// Radius
		2.0450603903063596f, 
	
		// 11 Vertices
		{{1.984f, 0.496f}, {1.984f, -0.496f}, {0.992f, -1.984f}, {-0.496f, -1.984f}, 
		{-1.984f, -0.496f}, {-0.992f, -0.496f}, {-1.984f, 0.496f}, {-0.992f, 1.984f}, 
		{0.0f, 0.496f}, {0.0f, 1.984f}, {0.992f, 1.984f}}
	),
	
	MeshData(
		// Name
		"AsteroidMedium4",
	
		// Radius
		2.2181794336797913f, 
	
		// 12 Vertices
		{{0.496f, 0.0f}, {1.984f, -0.496f}, {1.984f, -0.992f}, {0.496f, -1.984f}, 
		{-0.992f, -1.984f}, {-0.496f, -0.992f}, {-1.984f, -0.992f}, {-1.984f, 0.496f}, 
		{-0.992f, 1.984f}, {0.496f, 1.488f}, {0.992f, 1.984f}, {1.984f, 0.992f}
		}
	)
};

const std::array<MeshData, 4> kSmallAsteroids = {
	MeshData(
		// Name
		"AsteroidSmall1",
	
		// Radius
		1.1090897168398957f, 
	
		// 10 Vertices
		{{0.744f, 0.0f}, {0.992f, -0.496f}, {0.496f, -0.992f}, {0.0f, -0.496f}, 
		{-0.496f, -0.992f}, {-0.992f, -0.496f}, {-0.992f, 0.496f}, {-0.496f, 0.992f}, 
		{0.248f, 0.992f}, {0.992f, 0.496f}}
	),
	
	MeshData(
		// Name
		"AsteroidSmall2",
	
		// Radius
		1.1090897168398957f, 
	
		// 12 Vertices
		{{0.992f, 0.248f}, {0.496f, -0.248f}, {0.992f, -0.496f}, {0.496f, -0.992f}, 
		{0.0f, -0.744f}, {-0.496f, -0.992f}, {-0.992f, -0.496f}, {-0.744f, 0.0f}, 
		{-0.992f, 0.496f}, {-0.496f, 0.992f}, {-0.248f, 0.744f}, {0.496f, 0.992f}
		}
	),
	
	MeshData(
		// Name
		"AsteroidSmall3",
	
		// Radius
		1.0225301951531798f, 
	
		// 11 Vertices
		{{0.992f, 0.248f}, {0.992f, -0.248f}, {0.496f, -0.992f}, {-0.248f, -0.992f}, 
		{-0.992f, -0.248f}, {-0.496f, -0.248f}, {-0.992f, 0.248f}, {-0.496f, 0.992f}, 
		{0.0f, 0.248f}, {0.0f, 0.992f}, {0.496f, 0.992f}}
	),
	
	MeshData(
		// Name
		"AsteroidSmall4",
	
		// Radius
		1.1090897168398957f, 
	
		// 12 Vertices
		{{0.248f, 0.0f}, {0.992f, -0.248f}, {0.992f, -0.496f}, {0.248f, -0.992f}, 
		{-0.496f, -0.992f}, {-0.248f, -0.496f}, {-0.992f, -0.496f}, {-0.992f, 0.248f}, 
		{-0.496f, 0.992f}, {0.248f, 0.744f}, {0.496f, 0.992f}, {0.992f, 0.496f}
		}
	)
};

/////////////////////////////////////////////////
/////// Font Data
/////////////////////////////////////////////////

const float kFontWidth = 0.96f;
const float kFontHeight = 1.44f;

const std::array<IndexedMeshData, 42> kFont = {
	IndexedMeshData(
		// Name
		"0",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.48f, 0.72f}
		},	
	
		// 8 Indices
		{0, 1, 1, 2, 2, 3, 3, 0
		}
	),
	
	IndexedMeshData(
		// Name
		"1",
	
		// Radius
		0.7200000000000001f, 
	
		// 2 Vertices
		{{0.0f, -0.72f}, {0.0f, 0.72f}},	
	
		// 2 Indices
		{0, 1}
	),
	
	IndexedMeshData(
		// Name
		"2",
	
		// Radius
		0.8653323061113575f, 
	
		// 6 Vertices
		{{-0.48f, -0.72f}, {0.48f, -0.72f}, {0.48f, 0.0f}, {-0.48f, 0.0f}, 
		{-0.48f, 0.72f}, {0.48f, 0.72f}},	
	
		// 10 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		4, 5}
	),
	
	IndexedMeshData(
		// Name
		"3",
	
		// Radius
		0.8653323061113575f, 
	
		// 6 Vertices
		{{-0.48f, -0.72f}, {0.48f, -0.72f}, {0.48f, 0.0f}, {-0.48f, 0.0f}, 
		{0.48f, 0.72f}, {-0.48f, 0.72f}},	
	
		// 10 Indices
		{0, 1, 1, 2, 2, 3, 2, 4, 
		4, 5}
	),
	
	IndexedMeshData(
		// Name
		"4",
	
		// Radius
		0.8653323061113575f, 
	
		// 5 Vertices
		{{-0.48f, -0.72f}, {-0.48f, 0.0f}, {0.48f, 0.0f}, {0.48f, -0.72f}, 
		{0.48f, 0.72f}},	
	
		// 6 Indices
		{0, 1, 1, 2, 3, 4}
	),
	
	IndexedMeshData(
		// Name
		"5",
	
		// Radius
		0.8653323061113575f, 
	
		// 6 Vertices
		{{0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.0f}, {0.48f, 0.0f}, 
		{0.48f, 0.72f}, {-0.48f, 0.72f}},	
	
		// 10 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		4, 5}
	),
	
	IndexedMeshData(
		// Name
		"6",
	
		// Radius
		0.8653323061113575f, 
	
		// 5 Vertices
		{{-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.48f, 0.72f}, {0.48f, 0.0f}, 
		{-0.48f, 0.0f}},	
	
		// 8 Indices
		{0, 1, 1, 2, 2, 3, 3, 4
		}
	),
	
	IndexedMeshData(
		// Name
		"7",
	
		// Radius
		0.8653323061113575f, 
	
		// 3 Vertices
		{{-0.48f, -0.72f}, {0.48f, -0.72f}, {0.48f, 0.72f}},	
	
		// 4 Indices
		{0, 1, 1, 2}
	),
	
	IndexedMeshData(
		// Name
		"8",
	
		// Radius
		0.8653323061113575f, 
	
		// 6 Vertices
		{{0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.0f}, {-0.48f, 0.72f}, 
		{0.48f, 0.72f}, {0.48f, 0.0f}},	
	
		// 14 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		4, 5, 5, 0, 5, 2}
	),
	
	IndexedMeshData(
		// Name
		"9",
	
		// Radius
		0.8653323061113575f, 
	
		// 5 Vertices
		{{0.48f, 0.72f}, {0.48f, 0.0f}, {0.48f, -0.72f}, {-0.48f, -0.72f}, 
		{-0.48f, 0.0f}},	
	
		// 10 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		4, 1}
	),
	
	IndexedMeshData(
		// Name
		"A",
	
		// Radius
		0.5366563145999496f, 
	
		// 7 Vertices
		{{-0.48f, 0.72f}, {-0.48f, 0.24f}, {-0.48f, -0.24f}, {0.0f, -0.72f}, 
		{0.48f, -0.24f}, {0.48f, 0.24f}, {0.48f, 0.72f}},	
	
		// 14 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		4, 5, 5, 6, 1, 5}
	),
	
	IndexedMeshData(
		// Name
		"B",
	
		// Radius
		0.6788225099390857f, 
	
		// 9 Vertices
		{{0.24f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.24f, 0.72f}, 
		{0.48f, 0.48f}, {0.48f, 0.24f}, {0.24f, 0.0f}, {0.48f, -0.24f}, 
		{0.48f, -0.48f}},	
	
		// 18 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		4, 5, 5, 6, 6, 7, 7, 8, 
		8, 0}
	),
	
	IndexedMeshData(
		// Name
		"C",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.48f, 0.72f}
		},	
	
		// 6 Indices
		{0, 1, 1, 2, 2, 3}
	),
	
	IndexedMeshData(
		// Name
		"D",
	
		// Radius
		0.7200000000000001f, 
	
		// 6 Vertices
		{{-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.0f, 0.72f}, {0.48f, 0.24f}, 
		{0.48f, -0.24f}, {0.0f, -0.72f}},	
	
		// 12 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		4, 5, 5, 0}
	),
	
	IndexedMeshData(
		// Name
		"E",
	
		// Radius
		0.8653323061113575f, 
	
		// 6 Vertices
		{{0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.0f}, {-0.48f, 0.72f}, 
		{0.48f, 0.72f}, {0.24f, 0.0f}},	
	
		// 10 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		2, 5}
	),
	
	IndexedMeshData(
		// Name
		"F",
	
		// Radius
		0.8653323061113575f, 
	
		// 5 Vertices
		{{0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.0f}, {-0.48f, 0.72f}, 
		{0.24f, 0.0f}},	
	
		// 8 Indices
		{0, 1, 1, 2, 2, 3, 2, 4
		}
	),
	
	IndexedMeshData(
		// Name
		"G",
	
		// Radius
		0.8653323061113575f, 
	
		// 7 Vertices
		{{0.0f, 0.24f}, {0.48f, 0.24f}, {0.48f, 0.72f}, {-0.48f, 0.72f}, 
		{-0.48f, -0.72f}, {0.48f, -0.72f}, {0.48f, -0.24f}},	
	
		// 14 Indices
		{0, 1, 2, 2, 1, 2, 2, 3, 
		3, 4, 4, 5, 5, 6}
	),
	
	IndexedMeshData(
		// Name
		"H",
	
		// Radius
		0.8653323061113575f, 
	
		// 6 Vertices
		{{-0.48f, -0.72f}, {-0.48f, 0.0f}, {-0.48f, 0.72f}, {0.48f, 0.72f}, 
		{0.48f, 0.0f}, {0.48f, -0.72f}},	
	
		// 6 Indices
		{0, 2, 3, 5, 1, 4}
	),
	
	IndexedMeshData(
		// Name
		"I",
	
		// Radius
		0.8653323061113575f, 
	
		// 6 Vertices
		{{-0.48f, -0.72f}, {0.0f, -0.72f}, {0.48f, -0.72f}, {0.48f, 0.72f}, 
		{0.0f, 0.72f}, {-0.48f, 0.72f}},	
	
		// 6 Indices
		{0, 2, 5, 3, 1, 4}
	),
	
	IndexedMeshData(
		// Name
		"J",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{0.48f, -0.72f}, {0.48f, 0.72f}, {0.0f, 0.72f}, {-0.48f, 0.24f}
		},	
	
		// 6 Indices
		{0, 1, 1, 2, 2, 3}
	),
	
	IndexedMeshData(
		// Name
		"K",
	
		// Radius
		0.7589466384404111f, 
	
		// 5 Vertices
		{{-0.48f, -0.72f}, {-0.48f, 0.0f}, {-0.48f, 0.72f}, {0.24f, -0.72f}, 
		{0.24f, 0.72f}},	
	
		// 6 Indices
		{0, 2, 1, 3, 1, 4}
	),
	
	IndexedMeshData(
		// Name
		"L",
	
		// Radius
		0.8653323061113575f, 
	
		// 3 Vertices
		{{-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.48f, 0.72f}},	
	
		// 4 Indices
		{0, 1, 1, 2}
	),
	
	IndexedMeshData(
		// Name
		"M",
	
		// Radius
		0.8653323061113575f, 
	
		// 5 Vertices
		{{-0.48f, 0.72f}, {-0.48f, -0.72f}, {0.0f, -0.24f}, {0.48f, -0.72f}, 
		{0.48f, 0.72f}},	
	
		// 8 Indices
		{0, 1, 1, 2, 2, 3, 3, 4
		}
	),
	
	IndexedMeshData(
		// Name
		"N",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{-0.48f, 0.72f}, {-0.48f, -0.72f}, {0.48f, 0.72f}, {0.48f, -0.72f}
		},	
	
		// 6 Indices
		{0, 1, 1, 2, 2, 3}
	),
	
	IndexedMeshData(
		// Name
		"O",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.48f, 0.72f}
		},	
	
		// 8 Indices
		{0, 1, 1, 2, 2, 3, 3, 0
		}
	),
	
	IndexedMeshData(
		// Name
		"P",
	
		// Radius
		0.8653323061113575f, 
	
		// 5 Vertices
		{{-0.48f, 0.72f}, {-0.48f, 0.0f}, {-0.48f, -0.72f}, {0.48f, -0.72f}, 
		{0.48f, 0.0f}},	
	
		// 12 Indices
		{0, 1, 2, 2, 1, 2, 2, 3, 
		3, 4, 4, 1}
	),
	
	IndexedMeshData(
		// Name
		"Q",
	
		// Radius
		0.8653323061113575f, 
	
		// 7 Vertices
		{{0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.24f, 0.72f}, 
		{0.48f, 0.48f}, {0.48f, 0.72f}, {0.24f, 0.48f}},	
	
		// 12 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		4, 0, 6, 5}
	),
	
	IndexedMeshData(
		// Name
		"R",
	
		// Radius
		0.8653323061113575f, 
	
		// 6 Vertices
		{{0.48f, 0.0f}, {0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.0f}, 
		{-0.48f, 0.72f}, {0.48f, 0.72f}},	
	
		// 12 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		3, 0, 3, 5}
	),
	
	IndexedMeshData(
		// Name
		"S",
	
		// Radius
		0.8653323061113575f, 
	
		// 6 Vertices
		{{0.48f, -0.72f}, {-0.48f, -0.72f}, {-0.48f, 0.0f}, {0.48f, 0.0f}, 
		{0.48f, 0.72f}, {-0.48f, 0.72f}},	
	
		// 10 Indices
		{0, 1, 1, 2, 2, 3, 3, 4, 
		4, 5}
	),
	
	IndexedMeshData(
		// Name
		"T",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{0.48f, -0.72f}, {0.0f, -0.72f}, {-0.48f, -0.72f}, {0.0f, 0.72f}
		},	
	
		// 4 Indices
		{0, 2, 1, 3}
	),
	
	IndexedMeshData(
		// Name
		"U",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.48f, 0.72f}, {0.48f, -0.72f}
		},	
	
		// 6 Indices
		{0, 1, 1, 2, 2, 3}
	),
	
	IndexedMeshData(
		// Name
		"V",
	
		// Radius
		0.8653323061113575f, 
	
		// 3 Vertices
		{{-0.48f, -0.72f}, {0.0f, 0.72f}, {0.48f, -0.72f}},	
	
		// 4 Indices
		{0, 1, 1, 2}
	),
	
	IndexedMeshData(
		// Name
		"W",
	
		// Radius
		0.8653323061113575f, 
	
		// 5 Vertices
		{{-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.0f, 0.24f}, {0.48f, 0.72f}, 
		{0.48f, -0.72f}},	
	
		// 8 Indices
		{0, 1, 1, 2, 2, 3, 3, 4
		}
	),
	
	IndexedMeshData(
		// Name
		"X",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{-0.48f, -0.72f}, {-0.48f, 0.72f}, {0.48f, 0.72f}, {0.48f, -0.72f}
		},	
	
		// 4 Indices
		{0, 2, 3, 1}
	),
	
	IndexedMeshData(
		// Name
		"Y",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{0.48f, -0.72f}, {0.0f, -0.24f}, {-0.48f, -0.72f}, {0.0f, 0.72f}
		},	
	
		// 6 Indices
		{0, 1, 2, 1, 1, 3}
	),
	
	IndexedMeshData(
		// Name
		"Z",
	
		// Radius
		0.8653323061113575f, 
	
		// 4 Vertices
		{{-0.48f, -0.72f}, {0.48f, -0.72f}, {-0.48f, 0.72f}, {0.48f, 0.72f}
		},	
	
		// 6 Indices
		{0, 1, 1, 2, 2, 3}
	),
	
	IndexedMeshData(
		// Name
		" ",
	
		// Radius
		0.0f, 
	
		// 0 Vertices
		{},	
	
		// 0 Indices
		{}
	),
	
	IndexedMeshData(
		// Name
		"-",
	
		// Radius
		0.24000000000000002f, 
	
		// 2 Vertices
		{{-0.24f, 0.0f}, {0.24f, 0.0f}},	
	
		// 2 Indices
		{0, 1}
	),
	
	IndexedMeshData(
		// Name
		"©",
	
		// Radius
		0.6788225099390857f, 
	
		// 12 Vertices
		{{-0.24f, -0.72f}, {-0.48f, -0.48f}, {-0.48f, 0.48f}, {-0.24f, 0.72f}, 
		{0.24f, -0.72f}, {0.48f, -0.48f}, {0.48f, 0.48f}, {0.24f, 0.72f}, 
		{0.24f, -0.36f}, {-0.24f, -0.36f}, {-0.24f, 0.36f}, {0.24f, 0.36f}
		},	
	
		// 18 Indices
		{0, 1, 1, 2, 2, 3, 4, 5, 
		5, 6, 6, 7, 8, 9, 9, 10, 
		10, 11}
	),
	
	IndexedMeshData(
		// Name
		".",
	
		// Radius
		0.6118823416311343f, 
	
		// 4 Vertices
		{{-0.12f, 0.36f}, {-0.12f, 0.6f}, {0.12f, 0.6f}, {0.12f, 0.36f}
		},	
	
		// 8 Indices
		{3, 0, 0, 1, 1, 2, 2, 3
		}
	),
	
	IndexedMeshData(
		// Name
		":",
	
		// Radius
		0.6118823416311343f, 
	
		// 8 Vertices
		{{-0.12f, 0.36f}, {-0.12f, 0.6f}, {0.12f, 0.6f}, {0.12f, 0.36f}, 
		{-0.12f, -0.6f}, {-0.12f, -0.36f}, {0.12f, -0.36f}, {0.12f, -0.6f}
		},	
	
		// 16 Indices
		{3, 0, 0, 1, 1, 2, 2, 3, 
		4, 5, 5, 6, 6, 7, 7, 4
		}
	),
	
	IndexedMeshData(
		// Name
		",",
	
		// Radius
		0.7299315036357864f, 
	
		// 8 Vertices
		{{0.0f, 0.72f}, {-0.24f, 0.84f}, {-0.24f, 0.96f}, {0.0f, 0.84f}, 
		{0.12f, 0.72f}, {0.12f, 0.48f}, {0.0f, 0.48f}, {0.0f, 0.72f}
		},	
	
		// 14 Indices
		{5, 6, 6, 0, 0, 1, 1, 2, 
		2, 3, 3, 4, 4, 5}
	)
};

/////////////////////////////////////////////////
/////// Other Entities Data
/////////////////////////////////////////////////

const MeshData kShip = 

	MeshData(
		// Name
		"Ship",
	
		// Radius
		0.8195999023914047f, 
	
		// 5 Vertices
		{{0.0f, -0.896f}, {-0.512f, 0.64f}, {-0.256f, 0.384f}, {0.256f, 0.384f}, 
		{0.512f, 0.64f}}
	);

const MeshData kShipCollider = 

	MeshData(
		// Name
		"ShipCollider",
	
		// Radius
		0.7254901791202966f, 
	
		// 5 Vertices
		{{0.0f, -0.896f}, {-0.48f, 0.544f}, {-0.256f, 0.544f}, {0.256f, 0.544f}, 
		{0.48f, 0.544f}}
	);
