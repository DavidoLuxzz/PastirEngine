str_tilex,str_tiley = input("Enter tile size: ").split()
sizex = int(str_tilex)
sizey = int(str_tiley)

textures = ["block","stone", "grass","water", "plank","plank_on_water", "cobweb","plum","fence_full",
        "door","door_open","room","shade","block_corner","block_top","block_topdown","block_end",
        "black","fence_left","fence_right","fence_no_conn","line_corner","line_top","line_sides",
        "line_end", "fasada", "grass0", "grass1","grass2", "grass3","grass4", "grass5", "grass6",
        "grass7","grass8","grass9", "grass10","grass11","grass12", "grass13","grass14","grass15",
        "dirt0","dirt1", "cobble0","cobble1","cobble2", "cobble3","cobble4", "cobble5","cobble6",
        "cobble7"]
textures2 = ["W_start","S_start","A_start","D_start"]

coords = [] # list of strings
print("format = \"x y sizex sizey\"")
for texture in textures2:
    x,y = input(texture+": ").split()
    coords.append(str(int(x)*sizex)+" "+str(int(y)*sizey)+" "+str_tilex+" "+str_tiley)
    # print(coords)


for uv in coords:
    print(uv)
