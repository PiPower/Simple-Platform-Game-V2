struct VSOut
{
    float3 col: COLOR;
    float4 pos: SV_Position;
};

cbuffer cBuff
{
    float propotion;
};

VSOut main(float2 Pos:POSITION, float3 col : COLOR)
{
    VSOut vsout;
    vsout.pos = float4(Pos, 0, 1);
    vsout.col = col;
    //---------------------
   // vsout.pos.x = vsout.pos.x + OffsetX;
   // vsout.pos.y = vsout.pos.y + OffsetY;
    //---------------------
    vsout.pos.x = vsout.pos.x * propotion;


    vsout.col = col;
    return vsout;
}