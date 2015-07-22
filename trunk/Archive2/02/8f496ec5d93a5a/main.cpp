void DebugShapesRenderer::OnServerShapesList(const std::string&, const std::vector<uint8_t>& dump)
{
    volatile size_t read = 0;
    while (read < dump.size())
    {
        ShapeType type = (ShapeType)dump[read];
        float expire = *(float*)&dump[read + 1];
        read += 1 + sizeof(float);
        std::vector<float> args;
        args.resize(DebugShapes::argCount[(size_t)type]);
        for (auto& arg: args)
        {
            arg = *(float*)&dump[read];  // <-- segfault was happening here due to use of movaps instruction when compiled with -O2 and -flto and a bunch of other flags.
            read += sizeof(float);
        }
        mServerShapesList.emplace_back(
            expire,
            Shape{ type, std::move(args) });
    }
}