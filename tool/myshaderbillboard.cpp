#include "myshaderbillboard.h"

MyShaderBillboard::MyShaderBillboard()
{
    _pos        =   -1;
    _uv         =   -1;
    _normal     =   -1;
    _tagenl     =   -1;
    _biTagenl   =   -1;

    _MVP        =   -1;
    _matModel   =   -1;
    _matNormal  =   -1;
    _lightDir   =   -1;
    _cameraPos  =   -1;
    _texture    =   -1;
    _texture1   =   -1;
}

MyShaderBillboard::~MyShaderBillboard()
{

}

void MyShaderBillboard::initialize()
{
    const char* vs =
    {
        "uniform    mat4    _MVP;\n\
        uniform     mat4    _matModel;\n\
        uniform     mat3    _matNormal;\n\
        attribute   vec3    _pos; \n\
        attribute   vec2    _uv; \n\
        attribute   vec3    _normal; \n\ \
        attribute   vec3    _tagenl; \n\
        attribute   vec3    _biTagenl; \n\
        varying     vec2    _outUV;\n\
        varying     vec3    _outPos;\n\
        varying     mat3    _outTBN;\n\
        void main()\n\
        {\n\
            _outPos = (_matModel*vec4(_pos,1.0)).xyz;\n\
            vec3 nor = normalize(_matNormal*_normal);\n\
            vec3 bit = normalize(_matNormal*_biTagenl);\n\
            vec3 tag = normalize(_matNormal*_tagenl);\n\
            _outTBN  = mat3(tag,bit,nor);\n\
            gl_Position =   _MVP * vec4(_pos,1.0); \n\
            _outUV      =   _uv;\n\
        }"
    };
    const char* ps =
    {
        "precision  lowp        float;\n\
        uniform     sampler2D   _texture;\n\
        uniform     sampler2D   _texture1;\n\
        uniform     vec3        _lightDir;\n\
        uniform     vec3        _cameraPos;\n\
        varying     vec2        _outUV;\n\
        varying     vec3        _outPos;\n\
        varying     mat3        _outTBN;\n\
        void main()\n\
        {\n\
            gl_FragColor.rgb  = texture2D(_texture,_outUV).rgb;\n\
            vec3 normal   = normalize(_outTBN*(texture2D(_texture1,_outUV).rgb*2.0-1.0));\n\
            vec3 lightDir = normalize(_lightDir - _outPos);\n\
            vec3 cameraDir = normalize(_cameraPos- _outPos);\n\
            float NdotLD  = max(dot(normal,lightDir),0.1); \n\
            gl_FragColor.rgb   *= 0.2 + 0.8*NdotLD;\n\
            vec3    lightDirRef =   reflect(-lightDir, normal);\n\
            float   CDdotLDR    =   max(dot(cameraDir, lightDirRef), 0.0);\n\
            gl_FragColor.rgb    +=  pow(CDdotLDR, 64.0);\n\
        }"
    };

    bool    res =   createProgram(vs, ps);
    if(res)
    {
        _pos        =   glGetAttribLocation(_programId, "_pos");
        _uv         =   glGetAttribLocation(_programId, "_uv");
        _normal     =   glGetAttribLocation(_programId, "_normal");
        _tagenl     =   glGetAttribLocation(_programId, "_tagenl");
        _biTagenl   =   glGetAttribLocation(_programId, "_biTagenl");

        _MVP        =   glGetUniformLocation(_programId, "_MVP");
        _matModel   =   glGetUniformLocation(_programId, "_matModel");
        _matNormal  =   glGetUniformLocation(_programId, "_matNormal");
        _lightDir   =   glGetUniformLocation(_programId, "_lightDir");
        _cameraPos  =   glGetUniformLocation(_programId, "_cameraPos");
        _texture    =   glGetUniformLocation(_programId, "_texture");
        _texture1   =   glGetUniformLocation(_programId, "_texture1");
    }

}

void MyShaderBillboard::begin()
{
    glUseProgram(_programId);
    glEnableVertexAttribArray(_pos);
    glEnableVertexAttribArray(_uv);
    glEnableVertexAttribArray(_normal);
    glEnableVertexAttribArray(_tagenl);
    glEnableVertexAttribArray(_biTagenl);
}

void MyShaderBillboard::end()
{
    glDisableVertexAttribArray(_pos);
    glDisableVertexAttribArray(_uv);
    glDisableVertexAttribArray(_normal);
    glDisableVertexAttribArray(_tagenl);
    glDisableVertexAttribArray(_biTagenl);
    glUseProgram(0);
}
