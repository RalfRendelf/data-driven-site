ShaderEffect {
    width: 200
    height: 200

    vertexShader: "
        attribute highp vec4 posAttr;
        attribute highp vec2 texCoord;
        varying highp vec2 varyingTexCoord;
        void main() {
            gl_Position = posAttr;
            varyingTexCoord = texCoord;
        }
    "

    fragmentShader: "
        varying highp vec2 varyingTexCoord;
        uniform lowp float time;
        void main() {
            gl_FragColor = vec4(sin(time) * 0.5 + 0.5, cos(time) * 0.5 + 0.5, 0.5, 1.0);
        }
    "
}
