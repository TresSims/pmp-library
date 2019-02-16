//=============================================================================
// Copyright (C) 2011-2019 The pmp-library developers
//
// This file is part of the Polygon Mesh Processing Library.
// Distributed under the terms of the MIT license, see LICENSE.txt for details.
//
// SPDX-License-Identifier: MIT
//=============================================================================

#include "SurfaceMeshTest.h"

#include <pmp/io/SurfaceMeshIO.h>
#include <pmp/algorithms/SurfaceNormals.h>
#include <vector>

using namespace pmp;

class SurfaceMeshIOTest : public SurfaceMeshTest
{
};

TEST_F(SurfaceMeshIOTest, poly_io)
{
    add_triangle();
    mesh.write("test.pmp");
    mesh.clear();
    EXPECT_TRUE(mesh.is_empty());
    mesh.read("test.pmp");
    EXPECT_EQ(mesh.n_vertices(), size_t(3));
    EXPECT_EQ(mesh.n_faces(), size_t(1));

    // check malformed file names
    EXPECT_FALSE(mesh.write("testpolyly"));
}

TEST_F(SurfaceMeshIOTest, obj_io)
{
    add_triangle();
    SurfaceNormals::compute_vertex_normals(mesh);
    mesh.add_halfedge_property<TextureCoordinate>("h:texcoord",TextureCoordinate(0,0));
    mesh.write("test.obj");
    mesh.clear();
    EXPECT_TRUE(mesh.is_empty());
    mesh.read("test.obj");
    EXPECT_EQ(mesh.n_vertices(), size_t(3));
    EXPECT_EQ(mesh.n_faces(), size_t(1));
}

TEST_F(SurfaceMeshIOTest, off_io)
{
    add_triangle();
    SurfaceNormals::compute_vertex_normals(mesh);
    mesh.add_vertex_property<TextureCoordinate>("v:texcoord",TextureCoordinate(0,0));
    mesh.add_vertex_property<Color>("v:color",Color(0,0,0));
    IOOptions options(false, // binary
                      true, // normals
                      true, // colors
                      true); // texcoords
    mesh.write("test.off",options);
    mesh.clear();
    EXPECT_TRUE(mesh.is_empty());
    mesh.read("test.off");
    EXPECT_EQ(mesh.n_vertices(), size_t(3));
    EXPECT_EQ(mesh.n_faces(), size_t(1));
}

TEST_F(SurfaceMeshIOTest, off_io_binary)
{
    add_triangle();
    IOOptions options(true);
    mesh.write("binary.off", options);
    mesh.clear();
    EXPECT_TRUE(mesh.is_empty());
    mesh.read("binary.off");
    EXPECT_EQ(mesh.n_vertices(), size_t(3));
    EXPECT_EQ(mesh.n_faces(), size_t(1));
}

TEST_F(SurfaceMeshIOTest, stl_io)
{
    mesh.read("pmp-data/stl/icosahedron_ascii.stl");
    EXPECT_EQ(mesh.n_vertices(), size_t(12));
    EXPECT_EQ(mesh.n_faces(), size_t(20));
    EXPECT_EQ(mesh.n_edges(), size_t(30));
    mesh.clear();
    mesh.read("pmp-data/stl/icosahedron_binary.stl");
    EXPECT_EQ(mesh.n_vertices(), size_t(12));
    EXPECT_EQ(mesh.n_faces(), size_t(20));
    EXPECT_EQ(mesh.n_edges(), size_t(30));

    // try to write without normals being present
    EXPECT_FALSE(mesh.write("test.stl"));

    // the same with normals computed
    SurfaceNormals::compute_face_normals(mesh);
    EXPECT_TRUE(mesh.write("test.stl"));

    // try to write non-triangle mesh
    mesh.clear();
    add_quad();
    EXPECT_FALSE(mesh.write("test.stl"));
}

TEST_F(SurfaceMeshIOTest, ply_io)
{
    add_triangle();
    mesh.write("test.ply");
    mesh.clear();
    EXPECT_TRUE(mesh.is_empty());
    mesh.read("test.ply");
    EXPECT_EQ(mesh.n_vertices(), size_t(3));
    EXPECT_EQ(mesh.n_faces(), size_t(1));
}

TEST_F(SurfaceMeshIOTest, ply_io_binary)
{
    add_triangle();
    IOOptions options(true);
    mesh.write("binary.ply",options);
    mesh.clear();
    EXPECT_TRUE(mesh.is_empty());
    mesh.read("binary.ply");
    EXPECT_EQ(mesh.n_vertices(), size_t(3));
    EXPECT_EQ(mesh.n_faces(), size_t(1));
}

TEST_F(SurfaceMeshIOTest, xyz_io)
{
    add_triangle();
    mesh.write("test.xyz");
    mesh.clear();
    EXPECT_TRUE(mesh.is_empty());
    mesh.read("test.xyz");
    EXPECT_EQ(mesh.n_vertices(), size_t(3));
}
