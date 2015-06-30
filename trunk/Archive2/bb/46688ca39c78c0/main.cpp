#include <cstddef>
#include <cstdint>
#include <array>



namespace {



enum
{
    alignment = 8,
    max_block_size = 2048,
    num_blocks_per_pool = 256,
    pool_size = max_block_size * 2,
    num_pools = max_block_size / alignment,
    all_pools_size = max_block_size * max_block_size / alignment
};


constexpr std::size_t Align(std::size_t n)
{
    return (n + alignment - 1) & ~(alignment - 1);
}


constexpr std::size_t GetPoolIndex(std::size_t n)
{
    return (Align(n) + alignment - 1) & ~(alignment - 1);
}



struct PoolInfo
{
    uint8_t mNextFreeBlock = 0;
};


std::array<PoolInfo, num_pools> gPoolInfos;


template<std::size_t BlockSize>
struct Block
{
    std::array<uint8_t, BlockSize> mStorage;
};


template<typename T, typename U>
T& Decode(U& pod)
{
    static_assert(std::is_pod<U>::value, "");
    return *static_cast<T*>(static_cast<void*>(&pod));
}


struct PoolStorage
{
    std::array<uint8_t, pool_size> mStorage;
}__attribute__((aligned(2048)));


template<std::size_t BlockSize>
struct Pool : PoolStorage
{
    Pool()
    {
        for (auto i = 0; i != num_blocks_per_pool; ++i)
        {
            Decode<uint8_t>(mBlocks[i]) = i + 1;
        }
    }
    
    void* allocate(std::size_t)
    {
        PoolInfo& info = gPoolInfos[GetPoolIndex(BlockSize)];
        if (info.mNextFreeBlock)
        {
            auto result = &mBlocks[info.mNextFreeBlock];
            Decode<uint8_t>(mBlocks[info.mNextFreeBlock]) = Decode<uint8_t>(result);
            return result;
        }
        return ::operator new(BlockSize);
        
    }
    
    void deallocate(void* )
    {
    	// TODO
    }
    
    std::array<Block<BlockSize>, num_blocks_per_pool> mBlocks;
};


    Pool<8> gPool8;
    Pool<16> gPool16;
    Pool<24> gPool24;
    Pool<32> gPool32;
    Pool<40> gPool40;
    Pool<48> gPool48;
    Pool<56> gPool56;
    Pool<64> gPool64;
    Pool<72> gPool72;
    Pool<80> gPool80;
    Pool<88> gPool88;
    Pool<96> gPool96;
    Pool<104> gPool104;
    Pool<112> gPool112;
    Pool<120> gPool120;
    Pool<128> gPool128;
    Pool<136> gPool136;
    Pool<144> gPool144;
    Pool<152> gPool152;
    Pool<160> gPool160;
    Pool<168> gPool168;
    Pool<176> gPool176;
    Pool<184> gPool184;
    Pool<192> gPool192;
    Pool<200> gPool200;
    Pool<208> gPool208;
    Pool<216> gPool216;
    Pool<224> gPool224;
    Pool<232> gPool232;
    Pool<240> gPool240;
    Pool<248> gPool248;
    Pool<256> gPool256;
    Pool<264> gPool264;
    Pool<272> gPool272;
    Pool<280> gPool280;
    Pool<288> gPool288;
    Pool<296> gPool296;
    Pool<304> gPool304;
    Pool<312> gPool312;
    Pool<320> gPool320;
    Pool<328> gPool328;
    Pool<336> gPool336;
    Pool<344> gPool344;
    Pool<352> gPool352;
    Pool<360> gPool360;
    Pool<368> gPool368;
    Pool<376> gPool376;
    Pool<384> gPool384;
    Pool<392> gPool392;
    Pool<400> gPool400;
    Pool<408> gPool408;
    Pool<416> gPool416;
    Pool<424> gPool424;
    Pool<432> gPool432;
    Pool<440> gPool440;
    Pool<448> gPool448;
    Pool<456> gPool456;
    Pool<464> gPool464;
    Pool<472> gPool472;
    Pool<480> gPool480;
    Pool<488> gPool488;
    Pool<496> gPool496;
    Pool<504> gPool504;
    Pool<512> gPool512;
    Pool<520> gPool520;
    Pool<528> gPool528;
    Pool<536> gPool536;
    Pool<544> gPool544;
    Pool<552> gPool552;
    Pool<560> gPool560;
    Pool<568> gPool568;
    Pool<576> gPool576;
    Pool<584> gPool584;
    Pool<592> gPool592;
    Pool<600> gPool600;
    Pool<608> gPool608;
    Pool<616> gPool616;
    Pool<624> gPool624;
    Pool<632> gPool632;
    Pool<640> gPool640;
    Pool<648> gPool648;
    Pool<656> gPool656;
    Pool<664> gPool664;
    Pool<672> gPool672;
    Pool<680> gPool680;
    Pool<688> gPool688;
    Pool<696> gPool696;
    Pool<704> gPool704;
    Pool<712> gPool712;
    Pool<720> gPool720;
    Pool<728> gPool728;
    Pool<736> gPool736;
    Pool<744> gPool744;
    Pool<752> gPool752;
    Pool<760> gPool760;
    Pool<768> gPool768;
    Pool<776> gPool776;
    Pool<784> gPool784;
    Pool<792> gPool792;
    Pool<800> gPool800;
    Pool<808> gPool808;
    Pool<816> gPool816;
    Pool<824> gPool824;
    Pool<832> gPool832;
    Pool<840> gPool840;
    Pool<848> gPool848;
    Pool<856> gPool856;
    Pool<864> gPool864;
    Pool<872> gPool872;
    Pool<880> gPool880;
    Pool<888> gPool888;
    Pool<896> gPool896;
    Pool<904> gPool904;
    Pool<912> gPool912;
    Pool<920> gPool920;
    Pool<928> gPool928;
    Pool<936> gPool936;
    Pool<944> gPool944;
    Pool<952> gPool952;
    Pool<960> gPool960;
    Pool<968> gPool968;
    Pool<976> gPool976;
    Pool<984> gPool984;
    Pool<992> gPool992;
    Pool<1000> gPool1000;
    Pool<1008> gPool1008;
    Pool<1016> gPool1016;
    Pool<1024> gPool1024;
    Pool<1032> gPool1032;
    Pool<1040> gPool1040;
    Pool<1048> gPool1048;
    Pool<1056> gPool1056;
    Pool<1064> gPool1064;
    Pool<1072> gPool1072;
    Pool<1080> gPool1080;
    Pool<1088> gPool1088;
    Pool<1096> gPool1096;
    Pool<1104> gPool1104;
    Pool<1112> gPool1112;
    Pool<1120> gPool1120;
    Pool<1128> gPool1128;
    Pool<1136> gPool1136;
    Pool<1144> gPool1144;
    Pool<1152> gPool1152;
    Pool<1160> gPool1160;
    Pool<1168> gPool1168;
    Pool<1176> gPool1176;
    Pool<1184> gPool1184;
    Pool<1192> gPool1192;
    Pool<1200> gPool1200;
    Pool<1208> gPool1208;
    Pool<1216> gPool1216;
    Pool<1224> gPool1224;
    Pool<1232> gPool1232;
    Pool<1240> gPool1240;
    Pool<1248> gPool1248;
    Pool<1256> gPool1256;
    Pool<1264> gPool1264;
    Pool<1272> gPool1272;
    Pool<1280> gPool1280;
    Pool<1288> gPool1288;
    Pool<1296> gPool1296;
    Pool<1304> gPool1304;
    Pool<1312> gPool1312;
    Pool<1320> gPool1320;
    Pool<1328> gPool1328;
    Pool<1336> gPool1336;
    Pool<1344> gPool1344;
    Pool<1352> gPool1352;
    Pool<1360> gPool1360;
    Pool<1368> gPool1368;
    Pool<1376> gPool1376;
    Pool<1384> gPool1384;
    Pool<1392> gPool1392;
    Pool<1400> gPool1400;
    Pool<1408> gPool1408;
    Pool<1416> gPool1416;
    Pool<1424> gPool1424;
    Pool<1432> gPool1432;
    Pool<1440> gPool1440;
    Pool<1448> gPool1448;
    Pool<1456> gPool1456;
    Pool<1464> gPool1464;
    Pool<1472> gPool1472;
    Pool<1480> gPool1480;
    Pool<1488> gPool1488;
    Pool<1496> gPool1496;
    Pool<1504> gPool1504;
    Pool<1512> gPool1512;
    Pool<1520> gPool1520;
    Pool<1528> gPool1528;
    Pool<1536> gPool1536;
    Pool<1544> gPool1544;
    Pool<1552> gPool1552;
    Pool<1560> gPool1560;
    Pool<1568> gPool1568;
    Pool<1576> gPool1576;
    Pool<1584> gPool1584;
    Pool<1592> gPool1592;
    Pool<1600> gPool1600;
    Pool<1608> gPool1608;
    Pool<1616> gPool1616;
    Pool<1624> gPool1624;
    Pool<1632> gPool1632;
    Pool<1640> gPool1640;
    Pool<1648> gPool1648;
    Pool<1656> gPool1656;
    Pool<1664> gPool1664;
    Pool<1672> gPool1672;
    Pool<1680> gPool1680;
    Pool<1688> gPool1688;
    Pool<1696> gPool1696;
    Pool<1704> gPool1704;
    Pool<1712> gPool1712;
    Pool<1720> gPool1720;
    Pool<1728> gPool1728;
    Pool<1736> gPool1736;
    Pool<1744> gPool1744;
    Pool<1752> gPool1752;
    Pool<1760> gPool1760;
    Pool<1768> gPool1768;
    Pool<1776> gPool1776;
    Pool<1784> gPool1784;
    Pool<1792> gPool1792;
    Pool<1800> gPool1800;
    Pool<1808> gPool1808;
    Pool<1816> gPool1816;
    Pool<1824> gPool1824;
    Pool<1832> gPool1832;
    Pool<1840> gPool1840;
    Pool<1848> gPool1848;
    Pool<1856> gPool1856;
    Pool<1864> gPool1864;
    Pool<1872> gPool1872;
    Pool<1880> gPool1880;
    Pool<1888> gPool1888;
    Pool<1896> gPool1896;
    Pool<1904> gPool1904;
    Pool<1912> gPool1912;
    Pool<1920> gPool1920;
    Pool<1928> gPool1928;
    Pool<1936> gPool1936;
    Pool<1944> gPool1944;
    Pool<1952> gPool1952;
    Pool<1960> gPool1960;
    Pool<1968> gPool1968;
    Pool<1976> gPool1976;
    Pool<1984> gPool1984;
    Pool<1992> gPool1992;
    Pool<2000> gPool2000;
    Pool<2008> gPool2008;
    Pool<2016> gPool2016;
    Pool<2024> gPool2024;
    Pool<2032> gPool2032;
    Pool<2040> gPool2040;
    Pool<2048> gPool2048;
}





void* Allocate(std::size_t n)
{
    switch (Align(n))
    {
       
        case 8: return gPool8.allocate(1);
        case 16: return gPool16.allocate(1);
        case 24: return gPool24.allocate(1);
        case 32: return gPool32.allocate(1);
        case 40: return gPool40.allocate(1);
        case 48: return gPool48.allocate(1);
        case 56: return gPool56.allocate(1);
        case 64: return gPool64.allocate(1);
        case 72: return gPool72.allocate(1);
        case 80: return gPool80.allocate(1);
        case 88: return gPool88.allocate(1);
        case 96: return gPool96.allocate(1);
        case 104: return gPool104.allocate(1);
        case 112: return gPool112.allocate(1);
        case 120: return gPool120.allocate(1);
        case 128: return gPool128.allocate(1);
        case 136: return gPool136.allocate(1);
        case 144: return gPool144.allocate(1);
        case 152: return gPool152.allocate(1);
        case 160: return gPool160.allocate(1);
        case 168: return gPool168.allocate(1);
        case 176: return gPool176.allocate(1);
        case 184: return gPool184.allocate(1);
        case 192: return gPool192.allocate(1);
        case 200: return gPool200.allocate(1);
        case 208: return gPool208.allocate(1);
        case 216: return gPool216.allocate(1);
        case 224: return gPool224.allocate(1);
        case 232: return gPool232.allocate(1);
        case 240: return gPool240.allocate(1);
        case 248: return gPool248.allocate(1);
        case 256: return gPool256.allocate(1);
        case 264: return gPool264.allocate(1);
        case 272: return gPool272.allocate(1);
        case 280: return gPool280.allocate(1);
        case 288: return gPool288.allocate(1);
        case 296: return gPool296.allocate(1);
        case 304: return gPool304.allocate(1);
        case 312: return gPool312.allocate(1);
        case 320: return gPool320.allocate(1);
        case 328: return gPool328.allocate(1);
        case 336: return gPool336.allocate(1);
        case 344: return gPool344.allocate(1);
        case 352: return gPool352.allocate(1);
        case 360: return gPool360.allocate(1);
        case 368: return gPool368.allocate(1);
        case 376: return gPool376.allocate(1);
        case 384: return gPool384.allocate(1);
        case 392: return gPool392.allocate(1);
        case 400: return gPool400.allocate(1);
        case 408: return gPool408.allocate(1);
        case 416: return gPool416.allocate(1);
        case 424: return gPool424.allocate(1);
        case 432: return gPool432.allocate(1);
        case 440: return gPool440.allocate(1);
        case 448: return gPool448.allocate(1);
        case 456: return gPool456.allocate(1);
        case 464: return gPool464.allocate(1);
        case 472: return gPool472.allocate(1);
        case 480: return gPool480.allocate(1);
        case 488: return gPool488.allocate(1);
        case 496: return gPool496.allocate(1);
        case 504: return gPool504.allocate(1);
        case 512: return gPool512.allocate(1);
        case 520: return gPool520.allocate(1);
        case 528: return gPool528.allocate(1);
        case 536: return gPool536.allocate(1);
        case 544: return gPool544.allocate(1);
        case 552: return gPool552.allocate(1);
        case 560: return gPool560.allocate(1);
        case 568: return gPool568.allocate(1);
        case 576: return gPool576.allocate(1);
        case 584: return gPool584.allocate(1);
        case 592: return gPool592.allocate(1);
        case 600: return gPool600.allocate(1);
        case 608: return gPool608.allocate(1);
        case 616: return gPool616.allocate(1);
        case 624: return gPool624.allocate(1);
        case 632: return gPool632.allocate(1);
        case 640: return gPool640.allocate(1);
        case 648: return gPool648.allocate(1);
        case 656: return gPool656.allocate(1);
        case 664: return gPool664.allocate(1);
        case 672: return gPool672.allocate(1);
        case 680: return gPool680.allocate(1);
        case 688: return gPool688.allocate(1);
        case 696: return gPool696.allocate(1);
        case 704: return gPool704.allocate(1);
        case 712: return gPool712.allocate(1);
        case 720: return gPool720.allocate(1);
        case 728: return gPool728.allocate(1);
        case 736: return gPool736.allocate(1);
        case 744: return gPool744.allocate(1);
        case 752: return gPool752.allocate(1);
        case 760: return gPool760.allocate(1);
        case 768: return gPool768.allocate(1);
        case 776: return gPool776.allocate(1);
        case 784: return gPool784.allocate(1);
        case 792: return gPool792.allocate(1);
        case 800: return gPool800.allocate(1);
        case 808: return gPool808.allocate(1);
        case 816: return gPool816.allocate(1);
        case 824: return gPool824.allocate(1);
        case 832: return gPool832.allocate(1);
        case 840: return gPool840.allocate(1);
        case 848: return gPool848.allocate(1);
        case 856: return gPool856.allocate(1);
        case 864: return gPool864.allocate(1);
        case 872: return gPool872.allocate(1);
        case 880: return gPool880.allocate(1);
        case 888: return gPool888.allocate(1);
        case 896: return gPool896.allocate(1);
        case 904: return gPool904.allocate(1);
        case 912: return gPool912.allocate(1);
        case 920: return gPool920.allocate(1);
        case 928: return gPool928.allocate(1);
        case 936: return gPool936.allocate(1);
        case 944: return gPool944.allocate(1);
        case 952: return gPool952.allocate(1);
        case 960: return gPool960.allocate(1);
        case 968: return gPool968.allocate(1);
        case 976: return gPool976.allocate(1);
        case 984: return gPool984.allocate(1);
        case 992: return gPool992.allocate(1);
        case 1000: return gPool1000.allocate(1);
        case 1008: return gPool1008.allocate(1);
        case 1016: return gPool1016.allocate(1);
        case 1024: return gPool1024.allocate(1);
        case 1032: return gPool1032.allocate(1);
        case 1040: return gPool1040.allocate(1);
        case 1048: return gPool1048.allocate(1);
        case 1056: return gPool1056.allocate(1);
        case 1064: return gPool1064.allocate(1);
        case 1072: return gPool1072.allocate(1);
        case 1080: return gPool1080.allocate(1);
        case 1088: return gPool1088.allocate(1);
        case 1096: return gPool1096.allocate(1);
        case 1104: return gPool1104.allocate(1);
        case 1112: return gPool1112.allocate(1);
        case 1120: return gPool1120.allocate(1);
        case 1128: return gPool1128.allocate(1);
        case 1136: return gPool1136.allocate(1);
        case 1144: return gPool1144.allocate(1);
        case 1152: return gPool1152.allocate(1);
        case 1160: return gPool1160.allocate(1);
        case 1168: return gPool1168.allocate(1);
        case 1176: return gPool1176.allocate(1);
        case 1184: return gPool1184.allocate(1);
        case 1192: return gPool1192.allocate(1);
        case 1200: return gPool1200.allocate(1);
        case 1208: return gPool1208.allocate(1);
        case 1216: return gPool1216.allocate(1);
        case 1224: return gPool1224.allocate(1);
        case 1232: return gPool1232.allocate(1);
        case 1240: return gPool1240.allocate(1);
        case 1248: return gPool1248.allocate(1);
        case 1256: return gPool1256.allocate(1);
        case 1264: return gPool1264.allocate(1);
        case 1272: return gPool1272.allocate(1);
        case 1280: return gPool1280.allocate(1);
        case 1288: return gPool1288.allocate(1);
        case 1296: return gPool1296.allocate(1);
        case 1304: return gPool1304.allocate(1);
        case 1312: return gPool1312.allocate(1);
        case 1320: return gPool1320.allocate(1);
        case 1328: return gPool1328.allocate(1);
        case 1336: return gPool1336.allocate(1);
        case 1344: return gPool1344.allocate(1);
        case 1352: return gPool1352.allocate(1);
        case 1360: return gPool1360.allocate(1);
        case 1368: return gPool1368.allocate(1);
        case 1376: return gPool1376.allocate(1);
        case 1384: return gPool1384.allocate(1);
        case 1392: return gPool1392.allocate(1);
        case 1400: return gPool1400.allocate(1);
        case 1408: return gPool1408.allocate(1);
        case 1416: return gPool1416.allocate(1);
        case 1424: return gPool1424.allocate(1);
        case 1432: return gPool1432.allocate(1);
        case 1440: return gPool1440.allocate(1);
        case 1448: return gPool1448.allocate(1);
        case 1456: return gPool1456.allocate(1);
        case 1464: return gPool1464.allocate(1);
        case 1472: return gPool1472.allocate(1);
        case 1480: return gPool1480.allocate(1);
        case 1488: return gPool1488.allocate(1);
        case 1496: return gPool1496.allocate(1);
        case 1504: return gPool1504.allocate(1);
        case 1512: return gPool1512.allocate(1);
        case 1520: return gPool1520.allocate(1);
        case 1528: return gPool1528.allocate(1);
        case 1536: return gPool1536.allocate(1);
        case 1544: return gPool1544.allocate(1);
        case 1552: return gPool1552.allocate(1);
        case 1560: return gPool1560.allocate(1);
        case 1568: return gPool1568.allocate(1);
        case 1576: return gPool1576.allocate(1);
        case 1584: return gPool1584.allocate(1);
        case 1592: return gPool1592.allocate(1);
        case 1600: return gPool1600.allocate(1);
        case 1608: return gPool1608.allocate(1);
        case 1616: return gPool1616.allocate(1);
        case 1624: return gPool1624.allocate(1);
        case 1632: return gPool1632.allocate(1);
        case 1640: return gPool1640.allocate(1);
        case 1648: return gPool1648.allocate(1);
        case 1656: return gPool1656.allocate(1);
        case 1664: return gPool1664.allocate(1);
        case 1672: return gPool1672.allocate(1);
        case 1680: return gPool1680.allocate(1);
        case 1688: return gPool1688.allocate(1);
        case 1696: return gPool1696.allocate(1);
        case 1704: return gPool1704.allocate(1);
        case 1712: return gPool1712.allocate(1);
        case 1720: return gPool1720.allocate(1);
        case 1728: return gPool1728.allocate(1);
        case 1736: return gPool1736.allocate(1);
        case 1744: return gPool1744.allocate(1);
        case 1752: return gPool1752.allocate(1);
        case 1760: return gPool1760.allocate(1);
        case 1768: return gPool1768.allocate(1);
        case 1776: return gPool1776.allocate(1);
        case 1784: return gPool1784.allocate(1);
        case 1792: return gPool1792.allocate(1);
        case 1800: return gPool1800.allocate(1);
        case 1808: return gPool1808.allocate(1);
        case 1816: return gPool1816.allocate(1);
        case 1824: return gPool1824.allocate(1);
        case 1832: return gPool1832.allocate(1);
        case 1840: return gPool1840.allocate(1);
        case 1848: return gPool1848.allocate(1);
        case 1856: return gPool1856.allocate(1);
        case 1864: return gPool1864.allocate(1);
        case 1872: return gPool1872.allocate(1);
        case 1880: return gPool1880.allocate(1);
        case 1888: return gPool1888.allocate(1);
        case 1896: return gPool1896.allocate(1);
        case 1904: return gPool1904.allocate(1);
        case 1912: return gPool1912.allocate(1);
        case 1920: return gPool1920.allocate(1);
        case 1928: return gPool1928.allocate(1);
        case 1936: return gPool1936.allocate(1);
        case 1944: return gPool1944.allocate(1);
        case 1952: return gPool1952.allocate(1);
        case 1960: return gPool1960.allocate(1);
        case 1968: return gPool1968.allocate(1);
        case 1976: return gPool1976.allocate(1);
        case 1984: return gPool1984.allocate(1);
        case 1992: return gPool1992.allocate(1);
        case 2000: return gPool2000.allocate(1);
        case 2008: return gPool2008.allocate(1);
        case 2016: return gPool2016.allocate(1);
        case 2024: return gPool2024.allocate(1);
        case 2032: return gPool2032.allocate(1);
        case 2040: return gPool2040.allocate(1);
        case 2048: return gPool2048.allocate(1);
    }
    return ::operator new(n);
}



void Deallocate(void* ptr, std::size_t n)
{
    switch (Align(n))
    {
       
        case 8: return gPool8.deallocate(ptr);
        case 16: return gPool16.deallocate(ptr);
        case 24: return gPool24.deallocate(ptr);
        case 32: return gPool32.deallocate(ptr);
        case 40: return gPool40.deallocate(ptr);
        case 48: return gPool48.deallocate(ptr);
        case 56: return gPool56.deallocate(ptr);
        case 64: return gPool64.deallocate(ptr);
        case 72: return gPool72.deallocate(ptr);
        case 80: return gPool80.deallocate(ptr);
        case 88: return gPool88.deallocate(ptr);
        case 96: return gPool96.deallocate(ptr);
        case 104: return gPool104.deallocate(ptr);
        case 112: return gPool112.deallocate(ptr);
        case 120: return gPool120.deallocate(ptr);
        case 128: return gPool128.deallocate(ptr);
        case 136: return gPool136.deallocate(ptr);
        case 144: return gPool144.deallocate(ptr);
        case 152: return gPool152.deallocate(ptr);
        case 160: return gPool160.deallocate(ptr);
        case 168: return gPool168.deallocate(ptr);
        case 176: return gPool176.deallocate(ptr);
        case 184: return gPool184.deallocate(ptr);
        case 192: return gPool192.deallocate(ptr);
        case 200: return gPool200.deallocate(ptr);
        case 208: return gPool208.deallocate(ptr);
        case 216: return gPool216.deallocate(ptr);
        case 224: return gPool224.deallocate(ptr);
        case 232: return gPool232.deallocate(ptr);
        case 240: return gPool240.deallocate(ptr);
        case 248: return gPool248.deallocate(ptr);
        case 256: return gPool256.deallocate(ptr);
        case 264: return gPool264.deallocate(ptr);
        case 272: return gPool272.deallocate(ptr);
        case 280: return gPool280.deallocate(ptr);
        case 288: return gPool288.deallocate(ptr);
        case 296: return gPool296.deallocate(ptr);
        case 304: return gPool304.deallocate(ptr);
        case 312: return gPool312.deallocate(ptr);
        case 320: return gPool320.deallocate(ptr);
        case 328: return gPool328.deallocate(ptr);
        case 336: return gPool336.deallocate(ptr);
        case 344: return gPool344.deallocate(ptr);
        case 352: return gPool352.deallocate(ptr);
        case 360: return gPool360.deallocate(ptr);
        case 368: return gPool368.deallocate(ptr);
        case 376: return gPool376.deallocate(ptr);
        case 384: return gPool384.deallocate(ptr);
        case 392: return gPool392.deallocate(ptr);
        case 400: return gPool400.deallocate(ptr);
        case 408: return gPool408.deallocate(ptr);
        case 416: return gPool416.deallocate(ptr);
        case 424: return gPool424.deallocate(ptr);
        case 432: return gPool432.deallocate(ptr);
        case 440: return gPool440.deallocate(ptr);
        case 448: return gPool448.deallocate(ptr);
        case 456: return gPool456.deallocate(ptr);
        case 464: return gPool464.deallocate(ptr);
        case 472: return gPool472.deallocate(ptr);
        case 480: return gPool480.deallocate(ptr);
        case 488: return gPool488.deallocate(ptr);
        case 496: return gPool496.deallocate(ptr);
        case 504: return gPool504.deallocate(ptr);
        case 512: return gPool512.deallocate(ptr);
        case 520: return gPool520.deallocate(ptr);
        case 528: return gPool528.deallocate(ptr);
        case 536: return gPool536.deallocate(ptr);
        case 544: return gPool544.deallocate(ptr);
        case 552: return gPool552.deallocate(ptr);
        case 560: return gPool560.deallocate(ptr);
        case 568: return gPool568.deallocate(ptr);
        case 576: return gPool576.deallocate(ptr);
        case 584: return gPool584.deallocate(ptr);
        case 592: return gPool592.deallocate(ptr);
        case 600: return gPool600.deallocate(ptr);
        case 608: return gPool608.deallocate(ptr);
        case 616: return gPool616.deallocate(ptr);
        case 624: return gPool624.deallocate(ptr);
        case 632: return gPool632.deallocate(ptr);
        case 640: return gPool640.deallocate(ptr);
        case 648: return gPool648.deallocate(ptr);
        case 656: return gPool656.deallocate(ptr);
        case 664: return gPool664.deallocate(ptr);
        case 672: return gPool672.deallocate(ptr);
        case 680: return gPool680.deallocate(ptr);
        case 688: return gPool688.deallocate(ptr);
        case 696: return gPool696.deallocate(ptr);
        case 704: return gPool704.deallocate(ptr);
        case 712: return gPool712.deallocate(ptr);
        case 720: return gPool720.deallocate(ptr);
        case 728: return gPool728.deallocate(ptr);
        case 736: return gPool736.deallocate(ptr);
        case 744: return gPool744.deallocate(ptr);
        case 752: return gPool752.deallocate(ptr);
        case 760: return gPool760.deallocate(ptr);
        case 768: return gPool768.deallocate(ptr);
        case 776: return gPool776.deallocate(ptr);
        case 784: return gPool784.deallocate(ptr);
        case 792: return gPool792.deallocate(ptr);
        case 800: return gPool800.deallocate(ptr);
        case 808: return gPool808.deallocate(ptr);
        case 816: return gPool816.deallocate(ptr);
        case 824: return gPool824.deallocate(ptr);
        case 832: return gPool832.deallocate(ptr);
        case 840: return gPool840.deallocate(ptr);
        case 848: return gPool848.deallocate(ptr);
        case 856: return gPool856.deallocate(ptr);
        case 864: return gPool864.deallocate(ptr);
        case 872: return gPool872.deallocate(ptr);
        case 880: return gPool880.deallocate(ptr);
        case 888: return gPool888.deallocate(ptr);
        case 896: return gPool896.deallocate(ptr);
        case 904: return gPool904.deallocate(ptr);
        case 912: return gPool912.deallocate(ptr);
        case 920: return gPool920.deallocate(ptr);
        case 928: return gPool928.deallocate(ptr);
        case 936: return gPool936.deallocate(ptr);
        case 944: return gPool944.deallocate(ptr);
        case 952: return gPool952.deallocate(ptr);
        case 960: return gPool960.deallocate(ptr);
        case 968: return gPool968.deallocate(ptr);
        case 976: return gPool976.deallocate(ptr);
        case 984: return gPool984.deallocate(ptr);
        case 992: return gPool992.deallocate(ptr);
        case 1000: return gPool1000.deallocate(ptr);
        case 1008: return gPool1008.deallocate(ptr);
        case 1016: return gPool1016.deallocate(ptr);
        case 1024: return gPool1024.deallocate(ptr);
        case 1032: return gPool1032.deallocate(ptr);
        case 1040: return gPool1040.deallocate(ptr);
        case 1048: return gPool1048.deallocate(ptr);
        case 1056: return gPool1056.deallocate(ptr);
        case 1064: return gPool1064.deallocate(ptr);
        case 1072: return gPool1072.deallocate(ptr);
        case 1080: return gPool1080.deallocate(ptr);
        case 1088: return gPool1088.deallocate(ptr);
        case 1096: return gPool1096.deallocate(ptr);
        case 1104: return gPool1104.deallocate(ptr);
        case 1112: return gPool1112.deallocate(ptr);
        case 1120: return gPool1120.deallocate(ptr);
        case 1128: return gPool1128.deallocate(ptr);
        case 1136: return gPool1136.deallocate(ptr);
        case 1144: return gPool1144.deallocate(ptr);
        case 1152: return gPool1152.deallocate(ptr);
        case 1160: return gPool1160.deallocate(ptr);
        case 1168: return gPool1168.deallocate(ptr);
        case 1176: return gPool1176.deallocate(ptr);
        case 1184: return gPool1184.deallocate(ptr);
        case 1192: return gPool1192.deallocate(ptr);
        case 1200: return gPool1200.deallocate(ptr);
        case 1208: return gPool1208.deallocate(ptr);
        case 1216: return gPool1216.deallocate(ptr);
        case 1224: return gPool1224.deallocate(ptr);
        case 1232: return gPool1232.deallocate(ptr);
        case 1240: return gPool1240.deallocate(ptr);
        case 1248: return gPool1248.deallocate(ptr);
        case 1256: return gPool1256.deallocate(ptr);
        case 1264: return gPool1264.deallocate(ptr);
        case 1272: return gPool1272.deallocate(ptr);
        case 1280: return gPool1280.deallocate(ptr);
        case 1288: return gPool1288.deallocate(ptr);
        case 1296: return gPool1296.deallocate(ptr);
        case 1304: return gPool1304.deallocate(ptr);
        case 1312: return gPool1312.deallocate(ptr);
        case 1320: return gPool1320.deallocate(ptr);
        case 1328: return gPool1328.deallocate(ptr);
        case 1336: return gPool1336.deallocate(ptr);
        case 1344: return gPool1344.deallocate(ptr);
        case 1352: return gPool1352.deallocate(ptr);
        case 1360: return gPool1360.deallocate(ptr);
        case 1368: return gPool1368.deallocate(ptr);
        case 1376: return gPool1376.deallocate(ptr);
        case 1384: return gPool1384.deallocate(ptr);
        case 1392: return gPool1392.deallocate(ptr);
        case 1400: return gPool1400.deallocate(ptr);
        case 1408: return gPool1408.deallocate(ptr);
        case 1416: return gPool1416.deallocate(ptr);
        case 1424: return gPool1424.deallocate(ptr);
        case 1432: return gPool1432.deallocate(ptr);
        case 1440: return gPool1440.deallocate(ptr);
        case 1448: return gPool1448.deallocate(ptr);
        case 1456: return gPool1456.deallocate(ptr);
        case 1464: return gPool1464.deallocate(ptr);
        case 1472: return gPool1472.deallocate(ptr);
        case 1480: return gPool1480.deallocate(ptr);
        case 1488: return gPool1488.deallocate(ptr);
        case 1496: return gPool1496.deallocate(ptr);
        case 1504: return gPool1504.deallocate(ptr);
        case 1512: return gPool1512.deallocate(ptr);
        case 1520: return gPool1520.deallocate(ptr);
        case 1528: return gPool1528.deallocate(ptr);
        case 1536: return gPool1536.deallocate(ptr);
        case 1544: return gPool1544.deallocate(ptr);
        case 1552: return gPool1552.deallocate(ptr);
        case 1560: return gPool1560.deallocate(ptr);
        case 1568: return gPool1568.deallocate(ptr);
        case 1576: return gPool1576.deallocate(ptr);
        case 1584: return gPool1584.deallocate(ptr);
        case 1592: return gPool1592.deallocate(ptr);
        case 1600: return gPool1600.deallocate(ptr);
        case 1608: return gPool1608.deallocate(ptr);
        case 1616: return gPool1616.deallocate(ptr);
        case 1624: return gPool1624.deallocate(ptr);
        case 1632: return gPool1632.deallocate(ptr);
        case 1640: return gPool1640.deallocate(ptr);
        case 1648: return gPool1648.deallocate(ptr);
        case 1656: return gPool1656.deallocate(ptr);
        case 1664: return gPool1664.deallocate(ptr);
        case 1672: return gPool1672.deallocate(ptr);
        case 1680: return gPool1680.deallocate(ptr);
        case 1688: return gPool1688.deallocate(ptr);
        case 1696: return gPool1696.deallocate(ptr);
        case 1704: return gPool1704.deallocate(ptr);
        case 1712: return gPool1712.deallocate(ptr);
        case 1720: return gPool1720.deallocate(ptr);
        case 1728: return gPool1728.deallocate(ptr);
        case 1736: return gPool1736.deallocate(ptr);
        case 1744: return gPool1744.deallocate(ptr);
        case 1752: return gPool1752.deallocate(ptr);
        case 1760: return gPool1760.deallocate(ptr);
        case 1768: return gPool1768.deallocate(ptr);
        case 1776: return gPool1776.deallocate(ptr);
        case 1784: return gPool1784.deallocate(ptr);
        case 1792: return gPool1792.deallocate(ptr);
        case 1800: return gPool1800.deallocate(ptr);
        case 1808: return gPool1808.deallocate(ptr);
        case 1816: return gPool1816.deallocate(ptr);
        case 1824: return gPool1824.deallocate(ptr);
        case 1832: return gPool1832.deallocate(ptr);
        case 1840: return gPool1840.deallocate(ptr);
        case 1848: return gPool1848.deallocate(ptr);
        case 1856: return gPool1856.deallocate(ptr);
        case 1864: return gPool1864.deallocate(ptr);
        case 1872: return gPool1872.deallocate(ptr);
        case 1880: return gPool1880.deallocate(ptr);
        case 1888: return gPool1888.deallocate(ptr);
        case 1896: return gPool1896.deallocate(ptr);
        case 1904: return gPool1904.deallocate(ptr);
        case 1912: return gPool1912.deallocate(ptr);
        case 1920: return gPool1920.deallocate(ptr);
        case 1928: return gPool1928.deallocate(ptr);
        case 1936: return gPool1936.deallocate(ptr);
        case 1944: return gPool1944.deallocate(ptr);
        case 1952: return gPool1952.deallocate(ptr);
        case 1960: return gPool1960.deallocate(ptr);
        case 1968: return gPool1968.deallocate(ptr);
        case 1976: return gPool1976.deallocate(ptr);
        case 1984: return gPool1984.deallocate(ptr);
        case 1992: return gPool1992.deallocate(ptr);
        case 2000: return gPool2000.deallocate(ptr);
        case 2008: return gPool2008.deallocate(ptr);
        case 2016: return gPool2016.deallocate(ptr);
        case 2024: return gPool2024.deallocate(ptr);
        case 2032: return gPool2032.deallocate(ptr);
        case 2040: return gPool2040.deallocate(ptr);
        case 2048: return gPool2048.deallocate(ptr);
    }
}


void* ___test___(std::size_t n)
{
    return Allocate(n);
}