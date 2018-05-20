// old

const GLchar *PassthroughVertShader110Src =
    "#version 110\n"
    "varying vec2 TexCoord0; \n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    gl_Position = ftransform(); \n"
    "    TexCoord0 = gl_MultiTexCoord0.xy; \n"
    "}\n";

const GLchar *PaletteFragShader110Src =
    "#version 110\n"
    "uniform sampler2D PaletteTex; \n"
    "uniform sampler2D SurfaceTex; \n"
    "varying vec2 TexCoord0; \n"
    "\n"
    "void main()\n"
    "{\n"
    "   vec4 index = texture2D(SurfaceTex, TexCoord0); \n"
    "   vec4 texel = texture2D(PaletteTex, index.xy); \n"
    "   gl_FragColor = texel;\n"
    "}\n";


// new 

const GLchar *PassthroughVertShaderSrc =
    "#if __VERSION__ >= 130\n"
    "#define COMPAT_VARYING out\n"
    "#define COMPAT_ATTRIBUTE in\n"
    "#define COMPAT_TEXTURE texture\n"
    "#else\n"
    "#define COMPAT_VARYING varying \n"
    "#define COMPAT_ATTRIBUTE attribute \n"
    "#define COMPAT_TEXTURE texture2D\n"
    "#endif\n"
    "\n"
    "#ifdef GL_ES\n"
    "#define COMPAT_PRECISION mediump\n"
    "#else\n"
    "#define COMPAT_PRECISION\n"
    "#endif\n"
    "\n"
    "COMPAT_ATTRIBUTE vec4 VertexCoord;\n"
    "COMPAT_ATTRIBUTE vec4 COLOR;\n"
    "COMPAT_ATTRIBUTE vec4 TexCoord;\n"
    "COMPAT_VARYING vec4 COL0;\n"
    "COMPAT_VARYING vec4 TEX0;\n"
    "\n"
    "vec4 _oPosition1; \n"
    "uniform mat4 MVPMatrix;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 _oColor;\n"
    "    vec2 _otexCoord;\n"
    "    gl_Position = VertexCoord.x * MVPMatrix[0] + VertexCoord.y * MVPMatrix[1] + VertexCoord.z * MVPMatrix[2] + VertexCoord.w * MVPMatrix[3];\n"
    "    _oPosition1 = gl_Position;\n"
    "    _oColor = COLOR;\n"
    "    _otexCoord = TexCoord.xy;\n"
    "    COL0 = COLOR;\n"
    "    TEX0.xy = TexCoord.xy;\n"
    "}\n";


const GLchar *PaletteFragShaderSrc =
    "#if __VERSION__ >= 130\n"
    "#define COMPAT_VARYING in\n"
    "#define COMPAT_TEXTURE texture\n"
    "out vec4 FragColor;\n"
    "#else\n"
    "#define COMPAT_VARYING varying\n"
    "#define FragColor gl_FragColor\n"
    "#define COMPAT_TEXTURE texture2D\n"
    "#endif\n"
    "\n"
    "#ifdef GL_ES\n"
    "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
    "precision highp float;\n"
    "#else\n"
    "precision mediump float;\n"
    "#endif\n"
    "#define COMPAT_PRECISION mediump\n"
    "#else\n"
    "#define COMPAT_PRECISION\n"
    "#endif\n"
    "\n"
    "uniform sampler2D PaletteTex;\n"
    "uniform sampler2D SurfaceTex;\n"
    "COMPAT_VARYING vec4 TEX0;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 index = COMPAT_TEXTURE(SurfaceTex, TEX0.xy);\n"
    "    vec4 texel = COMPAT_TEXTURE(PaletteTex, index.xy);\n"
    "    FragColor = texel;\n"
    "}\n";
