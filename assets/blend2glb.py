import bpy
import sys

# get all args after "--"
argv = sys.argv[sys.argv.index("--") + 1:]

# join all meshes
bpy.ops.object.select_all(action="DESELECT")
bpy.ops.object.select_by_type(type="MESH")

# export obj
bpy.ops.export_scene.gltf(
    filepath=argv[0],
    export_format='GLB',
    check_existing=False)
