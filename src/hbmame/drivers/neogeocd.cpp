// license:GPL_2.0
// copyright-holders:Robbbert
#include "../mame/snk/neogeocd.cpp"

namespace {

class ngcd_hb : public ngcd_state
{
public:
	ngcd_hb(const machine_config &mconfig, device_type type, const char *tag)
		: ngcd_state(mconfig, type, tag)
		, m_cdrom(*this, "cdrom")
	{ }

	void neocd_hb(machine_config &config);

private:
	required_device<cdrom_image_device> m_cdrom;
};


void ngcd_hb::neocd_hb(machine_config &config)
{
	neogeo_base(config);
	neogeo_stereo(config);

	m_maincpu->set_addrmap(AS_PROGRAM, &ngcd_hb::neocd_main_map);
	m_maincpu->set_addrmap(m68000_base_device::AS_CPU_SPACE, &ngcd_hb::neocd_vector_map);

	m_audiocpu->set_addrmap(AS_PROGRAM, &ngcd_hb::neocd_audio_map);
	m_audiocpu->set_addrmap(AS_IO, &ngcd_hb::neocd_audio_io_map);

	m_screen->set_screen_update(FUNC(ngcd_hb::screen_update));

	// temporary until things are cleaned up
	LC89510_TEMP(config, m_tempcdc); // cd controller
	m_tempcdc->set_cdrom_tag("cdrom");
	m_tempcdc->set_is_neoCD(true);
	m_tempcdc->set_type1_interrupt_callback(FUNC(ngcd_hb::interrupt_callback_type1));
	m_tempcdc->set_type2_interrupt_callback(FUNC(ngcd_hb::interrupt_callback_type2));
	m_tempcdc->set_type3_interrupt_callback(FUNC(ngcd_hb::interrupt_callback_type3));

	NVRAM(config, "saveram", nvram_device::DEFAULT_ALL_0);

	NEOGEO_CONTROL_PORT(config, m_ctrl1, neogeo_controls, "joy", false);
	NEOGEO_CONTROL_PORT(config, m_ctrl2, neogeo_controls, "joy", false);

	CDROM(config, m_cdrom).set_interface("cdrom");
	m_cdrom->add_region("cdrom");

	m_ym->set_addrmap(0, &ngcd_hb::neocd_ym_map);
}

#define NEOCDZ_BASE \
	ROM_REGION16_BE( 0x80000, "mainbios", 0 ) \
	ROM_SYSTEM_BIOS( 0, "official",   "Official BIOS" ) \
	ROMX_LOAD("neocd.bin",    0x00000, 0x80000, CRC(df9de490) SHA1(7bb26d1e5d1e930515219cb18bcde5b7b23e2eda), ROM_GROUPWORD | ROM_REVERSE | ROM_BIOS(0)) \
	ROM_SYSTEM_BIOS( 1, "unibios32", "Universe BIOS (Hack, Ver. 3.2)" ) \
	ROMX_LOAD("uni-bioscd32.rom",    0x00000, 0x80000, CRC(0ffb3127) SHA1(5158b728e62b391fb69493743dcf7abbc62abc82), ROM_GROUPWORD | ROM_REVERSE | ROM_BIOS(1)) \
	ROM_SYSTEM_BIOS( 2, "unibios33", "Universe BIOS (Hack, Ver. 3.3)" ) \
	ROMX_LOAD("uni-bioscd33.rom",    0x00000, 0x80000, CRC(ff3abc59) SHA1(5142f205912869b673a71480c5828b1eaed782a8), ROM_GROUPWORD | ROM_REVERSE | ROM_BIOS(2)) \
	ROM_REGION( 0x20000, "spritegen:zoomy", 0 ) \
	ROM_LOAD( "000-lo.lo", 0x00000, 0x20000, CRC(5a86cff2) SHA1(5992277debadeb64d1c1c64b0a92d9293eaf7e4a) ) \
	DISK_REGION( "cdrom" )

#define rom_neocdb    rom_neocdz

 /*******
  SNK CD
**********/

ROM_START( 3countbncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "3countb", 0, SHA1(d31d934452ed3d90c73a5f7ec2f13b502293287b) )
ROM_END

ROM_START( 2020bbncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "2020bb", 0, SHA1(047a91393b7391d4ef772c706a034d57417a7a46) )
ROM_END

ROM_START( adkworldncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "adkworld", 0, SHA1(c99032d62ce5bf6be9b1dc37c70ef45a4dc37180) )
ROM_END

ROM_START( alpham2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "alpham2", 0, SHA1(be27801500ae7f4e40f2715dec343943fb0fb0e5) )
ROM_END

ROM_START( aodkncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "aodk", 0, SHA1(76d7972b3dd81fb476e4b89cd1b02e6ad794956d) )
ROM_END

ROM_START( aofncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "aof", 0, SHA1(77f4910e0b1d82a0b1d17594408bda368b619c0c) )
ROM_END

ROM_START( aof2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "aof2", 0, SHA1(91f57d4a159e95a63c5992a69a8e7d02934432f0) )
ROM_END

ROM_START( aof3ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "aof3", 0, SHA1(275e2265e56d719d55a80cac811d421e0f81c669) )
ROM_END

ROM_START( aof3ancd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "aof3a", 0, SHA1(39502261dc15f4279659ed074b1b4e62b683f266) )
ROM_END

ROM_START( b2bncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "bbbuster", 0, SHA1(2112eca62613c4ebaff3a62334b6395009c05c37) )
ROM_END

ROM_START( bjourneyncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "bjourney", 0, SHA1(b1063594b9e214765b95e0446c041c2a5663ae20) )
ROM_END

ROM_START( breakersncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "breakers", 0, SHA1(f203ef8f2a431a2e841af09deaedda3d33238104) )
ROM_END

ROM_START( bstarsncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "bstars", 0, SHA1(85fa71ab8576dd7bcc9717111297926ce6cec29e) )
ROM_END

ROM_START( bstars2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "bstars2", 0, SHA1(e8963b17212889ac5307e8d40f940f8d941cd46a) )
ROM_END

ROM_START( burningfncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "burningf", 0, SHA1(fb851b5fc2bc5ce2addf8c1bae5b65401c10eceb) )
ROM_END

ROM_START( cpbarrelncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "cpbarrel", 0, SHA1(c36ef17f7c00a25ca443f3aac01afffa24539de6) )
ROM_END

ROM_START( crswordncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "crsword", 0, SHA1(854759d12584d2bded3bd6355016ac1302acf973) )
ROM_END

ROM_START( crswd2blncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "crsword2", 0, SHA1(dc65e9a937bfc912c3fdaff0b8200bfd4df4c34c) )
ROM_END

ROM_START( cyberlipncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "cyberlip", 0, SHA1(4f4667df89005623200bb6a0a49d55beda1128db) )
ROM_END

ROM_START( doubledrncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "doubledr", 0, SHA1(404856deac6875ec1fac00fa36c2aed1b6900c09) )
ROM_END

ROM_START( doubledrancd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "doubledra", 0, SHA1(64bf06de31105900dacbdd927ef635f71d264725) )
ROM_END

ROM_START( fatfurspncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "fatfursp", 0, SHA1(a4a3a5b7c95214bec4b77d1a91686a83f6600638) )
ROM_END

ROM_START( fatfury1ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "fatfury1", 0, SHA1(098d6b48b45afad41bb17467e460990069f9385b) )
ROM_END

ROM_START( fatfury2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "fatfury2", 0, SHA1(886f605d800cdab23de381135a3938bcbd821662) )
ROM_END

ROM_START( fatfury3ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "fatfury3", 0, SHA1(5bcf25e0a4f01389e028632fa2f2a13f31444a87) )
ROM_END

ROM_START( fatfury3ancd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "fatfury3a", 0, SHA1(3a808e3bda8b1eb77e1f30bfd6e38e1b303b11ec) )
ROM_END

ROM_START( fbfrenzyncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "fbfrenzy", 0, SHA1(e2fed1652c5d513edaae11481b4345e3b19fd760) )
ROM_END

ROM_START( froman2bncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "froman2b", 0, SHA1(63c2b6c8cccfbcba9c41efb61954db9885ff9869) )
ROM_END

ROM_START( galaxyfgncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "galaxyfg", 0, SHA1(65ca73d11d98e9c9e26bf0753e52378188c79471) )
ROM_END

ROM_START( gowcaizrncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "gowcaizr", 0, SHA1(9a645a7dc3f723b55393090f11d5ae425f7411c6) )
ROM_END

ROM_START( gpilotsncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "gpilots", 0, SHA1(77f8425c27c314aa746951c517f9a44c2624baae) )
ROM_END

ROM_START( ironcladncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ironclad", 0, SHA1(4d518370686853c727eb300a91c0f070c3333225) )
ROM_END

ROM_START( janshinncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "janshin", 0, SHA1(074807c2a48f5c915a253e7b9bff2b8a3ad0ced3) )
ROM_END

ROM_START( joyjoyncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "joyjoy", 0, SHA1(738d0194042cc9c7093bcdbacfbb99f97dc07ba2) )
ROM_END

ROM_START( kabukiklncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kabukikl", 0, SHA1(922c307ef433c412d65a1ff3f8a8327fdfb1d1c9) )
ROM_END

ROM_START( karnovrncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "karnovr", 0, SHA1(89acc598b304e97749f632c4883935cf1f41100e) )
ROM_END

ROM_START( kof94ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof94", 0, SHA1(a6a461dc12ab4a0bb4385d2800a97b64a5792414) )
ROM_END

ROM_START( kof94ancd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof94a", 0, SHA1(60319c764eef1814825b3440bb0838f3f16fd447) )
ROM_END

ROM_START( kof95ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof95", 0, SHA1(dee363caf747ecd92e9e98b88094aecf181173e4) )
ROM_END

ROM_START( kof95ancd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof95a", 0, SHA1(67f0ce0da3585043b3813be2fc0b7664b60c32d3) )
ROM_END

ROM_START( kof96ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof96", 0, SHA1(e162d33d5a33049bf26226a651b359815efae16b) )
ROM_END

ROM_START( kof96ancd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof96a", 0, SHA1(a3b663994339fd6c8244fed1865895a87e8365b2) )
ROM_END

ROM_START( kof96colncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof96col", 0, SHA1(4f0fa12fc1e6b77e08fbbfa84366dbb04ca09f32) )
ROM_END

ROM_START( kof97ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof97", 0, SHA1(3985560edfda8e5095e888b8fd8f5ae6a9a820dd) )
ROM_END

ROM_START( kof98ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof98", 0, SHA1(a9347d7ca911be575fc1d4da01b9376f05057181) )
ROM_END

ROM_START( kof99ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kof99", 0, SHA1(813e7880f72e19074beb8cc1d96eb4f9e2f87c09) )
ROM_END

ROM_START( kotm2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "kotm2", 0, SHA1(c041b07f6057b818fb666b450e65b227c1f0c56d) )
ROM_END

ROM_START( lastbladncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "lastblad", 0, SHA1(72dd53d44e0b253246e4d1a3815f7c4e9d27c5ec) )
ROM_END

ROM_START( lastbld2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "lastbld2", 0, SHA1(d4a4dc25b27ecb26f64242acf06fe6da98ee3777) )
ROM_END

ROM_START( lasthopencd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "lasthope", 0, SHA1(4cf60613098531b49c447a2b223aeb49a6395fd2) )
ROM_END

ROM_START( lbowlingncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "lbowling", 0, SHA1(ca657fa76e16ae70745a6938770677c523daa041) )
ROM_END

ROM_START( looptrisncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "looptris", 0, SHA1(890b3a08bf9a88d5ae6d4fbd73bd903ad929af64) )
ROM_END

ROM_START( looptrspncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "looptrisp", 0, SHA1(154085e56b1bbbba4a866796c3f385da7cb6a3ed) )
ROM_END

ROM_START( lresortncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "lresort", 0, SHA1(372b9642cf861d3c7507b8485fc43fc144b16874) )
ROM_END

ROM_START( magdrop2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "magdrop2", 0, SHA1(69135e129dd3587910f3b6042175788298e31a71) )
ROM_END

ROM_START( maglordncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "maglord", 0, SHA1(e537fefc2179c2017ebb1d0794f77b1d18581555) )
ROM_END

ROM_START( mahretsuncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "mahretsu", 0, SHA1(8cc5def122d2638d7c63f02922150cc046ef3c1a) )
ROM_END

ROM_START( moshougincd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "mosyougi", 0, SHA1(d61ec46215b07bb8d7f070e439212641cc409792) )
ROM_END

ROM_START( mslugncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "mslug", 0, SHA1(b4f83b0b7046e9445f9cc16c40e57fd84b575ef9) )
ROM_END

ROM_START( mslug2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "mslug2", 0, SHA1(8cc8fc89d4effec887c25ca18d6caf4893572302) )
ROM_END

ROM_START( mutnatncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "mutnat", 0, SHA1(624efc927077f87f7fea2d5b14bf3cf8c68a5514) )
ROM_END

ROM_START( nam1975ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "nam1975", 0, SHA1(8a0ea9a98551286da76bb75137211b9f0aec5541) )
ROM_END

ROM_START( ncombatncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ncombat", 0, SHA1(713aefb92722b41926da4676adba6ea428420b19) )
ROM_END

ROM_START( ncommandncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ncommand", 0, SHA1(55e4e119a9fb3cd284eda0712f1fd79c1aced861) )
ROM_END

ROM_START( neodriftncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "neodrift", 0, SHA1(9bad0585e54fc505c635d7d6e0ded79c175c6c8d) )
ROM_END

ROM_START( ngcdspecncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ngcdspec", 0, SHA1(20ceb3e2cb21c6ccad99e0e21dc990affb4ecc39) )
ROM_END

ROM_START( ninjamasncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ninjamas", 0, SHA1(b2a9a6cb38d66af1e02450a2967b4eeff39e2ad6) )
ROM_END

ROM_START( overtopncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "overtop", 0, SHA1(e5d510ffa771cc8caa5a6ca7465ac69fe75ae3e5) )
ROM_END

ROM_START( pbobblenncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "pbobble", 0, SHA1(e9ae51499f1790b402307c0d1c8a62c2ff0cfea9) )
ROM_END

ROM_START( pgoalncdncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "pgoal", 0, SHA1(8e70456d560e6c8f1a484af86b953d9ed6bbf724) )
ROM_END

ROM_START( pspikes2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "pspikes2", 0, SHA1(a0b7b551971f2f0c76b92ad09f271f0d96575a5a) )
ROM_END

ROM_START( pulstarncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "pulstar", 0, SHA1(a7836434d5180beb460c3100c29812dd3928228c) )
ROM_END

ROM_START( quizkofncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "quizkof", 0, SHA1(e361db324e54e4e523e46c2803c831e3b51750de) )
ROM_END

ROM_START( ragnagrdncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ragnagrd", 0, SHA1(ae219a7382645c648a78a2126f3cd1dfc01cd708) )
ROM_END

ROM_START( rbff1ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "rbff1", 0, SHA1(634906800d14029e0e86f1ff531139ec47e213c6) )
ROM_END

ROM_START( rbff2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "rbff2", 0, SHA1(d738ff116843cedeb719d5ee033d98e05f62d92e) )
ROM_END

ROM_START( rbffspecncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "rbffspec", 0, SHA1(22da9b42359f4c9281dd9569baf043a6f86eb746) )
ROM_END

ROM_START( ridheroncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ridhero", 0, SHA1(0289f10c5bfffad8575cda05088fad52e256474d) )
ROM_END

ROM_START( roboarmyncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "roboarmy", 0, SHA1(1e3a592681df2ec8e7c983c7a2192ae8ae563121) )
ROM_END

ROM_START( samshoncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "samsho", 0, SHA1(26181f36ae317a2eb93ade832d2cf0b9ccfd1c42) )
ROM_END

ROM_START( samsho2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "samsho2", 0, SHA1(ee5a32a77152f7408c62dc7321e5f2adf322d46c) )
ROM_END

ROM_START( samsho3ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "samsho3", 0, SHA1(ad0b2dee64bf8b34e27ec2c1435859d568b49981) )
ROM_END

ROM_START( samsho4ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "samsho4", 0, SHA1(b90bff26f7977049935ca3d761f3ce692f117813) )
ROM_END

ROM_START( samsprpgncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "samsprpg", 0, SHA1(5df33f9533c2bc55c3354790bcafb1350039b438) )
ROM_END

ROM_START( savagerencd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "savagere", 0, SHA1(67cdf5abc7f52b8c2f9d7ad5cec73528d6a456bd) )
ROM_END

ROM_START( sengokuncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "sengoku", 0, SHA1(eac1b1a0b884bcd4d9e02891c85c34ea182ccdb1) )
ROM_END

ROM_START( sengoku2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "sengoku2", 0, SHA1(52f016131ccd4f5835f5ddf35b20114c474c62d9) )
ROM_END

ROM_START( socbrawlncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "socbrawl", 0, SHA1(97e9a937f211536197a96a9cbcafaec0ffc21662) )
ROM_END

ROM_START( sonicwi2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "sonicwi2", 0, SHA1(12a453dd787b6407f9bf18eec044095edb5c4511) )
ROM_END

ROM_START( sonicwi3ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "sonicwi3", 0, SHA1(3bd2b3931429d67e5443a2e931a6f75041cb3030) )
ROM_END

ROM_START( ssidekincd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ssideki", 0, SHA1(9bda953cb1b5354cb19ec3f8d2792de6bd1fba1a) )
ROM_END

ROM_START( ssideki2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ssideki2", 0, SHA1(ef2a5fee5502561d25922aad1656319de18c72a0) )
ROM_END

ROM_START( ssideki3ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ssideki3", 0, SHA1(ac8e645615318789535513b5861d99d6e45b99f9) )
ROM_END

ROM_START( stakwinncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "stakwin", 0, SHA1(e72ce998b2d91542df5ae05ac0714284b6926e5d) )
ROM_END

ROM_START( strhoopncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "strhoop", 0, SHA1(7bb971e4dd218a65c40e0f2f368711a6889e1b05) )
ROM_END

ROM_START( superspyncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "superspy", 0, SHA1(46297a94d8db0e4e6abaebbf33e4560cdec9be85) )
ROM_END

ROM_START( tophuntrncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "tophuntr", 0, SHA1(fdde6325416fabf1929b61f64c87a5398e6e8e5d) )
ROM_END

ROM_START( totcncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "totc", 0, SHA1(95c9e0b42410ac4e384529b3c067cb55e9b0e537) )
ROM_END

ROM_START( tpgolfncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "tpgolf", 0, SHA1(fe6326f015917a87fd1f436311be6f48def2b2cf) )
ROM_END

ROM_START( trallyncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "trally", 0, SHA1(07a394aaf9937206f4bd61e2c9f46afe1a43aecb) )
ROM_END

ROM_START( turfmastncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "turfmast", 0, SHA1(806597142c6e7939009494c8f3a84fcbdc1fca38) )
ROM_END

ROM_START( twinsprincd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "twinspri", 0, SHA1(169ad6845fe9baa6ca3e08f92e554ede71b3b13e) )
ROM_END

ROM_START( viewpoinncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "viewpoin", 0, SHA1(8a13861b34cbe5953843a535c7b50d691aefa069) )
ROM_END

ROM_START( wh1ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "wh1", 0, SHA1(10b4a5ef5613982edbc07da1894208ec6a468583) )
ROM_END

ROM_START( wh2ncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "wh2", 0, SHA1(4dba3f8107f798c089d8be7b1b1fbe2dfb4e1d8b) )
ROM_END

ROM_START( wh2jncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "wh2j", 0, SHA1(b2ce705d16b82963a2eafbbefe37975225b7b145) )
ROM_END

ROM_START( whpncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "whp", 0, SHA1(7d444937c98b08845a00f965ced83e6677109cb7) )
ROM_END

ROM_START( wjammersncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "wjammers", 0, SHA1(2d4dc090fa7d55f04c2f6484f1e892d93ce42aa4) )
ROM_END

ROM_START( xenoncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "xenocris", 0, SHA1(792ee3aa806d06163b4d613f47d8ac9802a20c92) )
ROM_END

ROM_START( zintrckbncd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "zintrick", 0, SHA1(46ab081316ffc6d5cca76fee679e80270fe1a8ab) )
ROM_END

 /*********
  HomeBrew
*************/

ROM_START( alice_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "819", 0, SHA1(a9dfafadc121be3ea991a0a85377622d9a3a535f) )
ROM_END

ROM_START( chelnov_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "chelnov", 0, SHA1(45d1902421e97e642d02a485dcd06f9780d94fd1) )
ROM_END

ROM_START( diff_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "820", 0, SHA1(04594dcd984f21203bb5489c4612d28a93d6c7cd) )
ROM_END

ROM_START( eira_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "817", 0, SHA1(c441932e9566f0647888ceeff3229622ae9609a8) )
ROM_END

ROM_START( ffury_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "ffuryae", 0, SHA1(c0e0e4180bddc3691ab59e5e2900ab3dcc9080f7) )
ROM_END

ROM_START( fukkireta_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "822", 0, SHA1(57fd82eb079a4e3951b769bd6cc9afa84394aaaa) )
ROM_END

ROM_START( gaxe_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "gaxe", 0, SHA1(3b7c9d7e1d3390a3610e436edf4425b9a40859b6) )
ROM_END

ROM_START( gaxearr_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "gaxearr", 0, SHA1(39bf69b8dfd73c2033a09f3e518db45194d2d7b8) )
ROM_END

ROM_START( natademo_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "818", 0, SHA1(22ac0c741defe9d792b9f38cd48dd0742140ec0a) )
ROM_END

ROM_START( ngdark_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "805", 0, SHA1(940b8b162ddf98cafebbd0bd7a3e43fae455d0cf) )
ROM_END

ROM_START( noneon_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "823", 0, SHA1(daa286dc1e9c651e3f54802fd632f03dce10f3e4) )
ROM_END

ROM_START( ntris3d_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "825", 0, SHA1(a06e149504f62dc94ecfe46d0d094bb9ca9f79a7) )
ROM_END

ROM_START( phoenix_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "815", 0, SHA1(109fa573867236750396fcbf1037d47a90027415) )
ROM_END

ROM_START( pong_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "827", 0, SHA1(5f2a993bce41f18e6562e0c113cc08fd7bc8060f) )
ROM_END

ROM_START( pow_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "pow2", 0, SHA1(9017ead20ecbfeb25c6c36282423c90375403b32) )
ROM_END

ROM_START( shinobiarr_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "shinobiarr", 0, SHA1(3f93364dc54a91eadeddf52675a7043b191675ba) )
ROM_END

ROM_START( speedball_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "829", 0, SHA1(550726ee523e6dc32a961e4cdbc63a6c2e2a4bc8) )
ROM_END

ROM_START( ssrpg_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "828", 0, SHA1(2bc6a30d305c52e9189efe9840d34370ed260300) )
ROM_END

ROM_START( subspecies_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "824", 0, SHA1(59a23f8a30d8b0422734f8609f3ebea251de94e1) )
ROM_END

ROM_START( visualnovel_cd )
	NEOCDZ_BASE
	DISK_IMAGE_READONLY( "821", 0, SHA1(70cde7435cec39241ff5f5d704f9f58193c6f1ac) )
ROM_END

} // anonymous namespace

/*    YEAR  NAME           PARENT    MACHINE      INPUT    CLASS        INIT    */
GAME( 1996, neocdb,         0,       neocd_ntsc,  neocd,  ngcd_state, init_neocdz, ROT0,"SNK", "Neo-Geo CDZ", MACHINE_IS_BIOS_ROOT | MACHINE_SUPPORTS_SAVE )

/*    YEAR  NAME           PARENT      MACHINE   INPUT   CLASS       INIT     MONITOR COMPANY  */
/* SNK CD */
GAME( 1995, 3countbncd,    3countb,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "3 Count Bout / Fire Suplex (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, 2020bbncd,     2020bb,    neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK / Pallas", "2020 Super Baseball (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, adkworldncd,   adkw,      neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "ADK World (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, alpham2ncd,    alpham2,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Alpha Mission II / ASO II - Last Guardian (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, aodkncd,       aodk,      neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK / SNK", "Aggressors of Dark Kombat / Tsuukai GANGAN Koushinkyoku (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, aofncd,        aof,       neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Art of Fighting / Ryuuko no Ken (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, aof2ncd,       aof2,      neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Art of Fighting 2 / Ryuuko no Ken 2 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, aof3ncd,       aof3,      neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Art of Fighting 3 - The Path of the Warrior / Art of Fighting - Ryuuko no Ken Gaiden (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, aof3ancd,      aof3,      neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Art of Fighting 3 - The Path of the Warrior / Art of Fighting - Ryuuko no Ken Gaiden (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 2011, b2bncd,        b2b,       neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Neo Conception International", "Bang Bang Busters (France) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, bjourneyncd,   bjourney,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Blue's Journey / Raguy (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, breakersncd,   breakers,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Visco", "Breakers (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, bstarsncd,     bstars,    neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Baseball Stars Professional (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, bstars2ncd,    bstars2,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Baseball Stars 2 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, burningfncd,   burningf,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Burning Fight (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 2024, cpbarrelncd,    0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Neo Byte Force", "Captain Barrel (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, crswordncd,    crsword,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Crossed Swords (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, crswd2blncd,   crswd2bl,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK","Crossed Swords 2 (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, cyberlipncd,   cyberlip,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Cyber-Lip (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
//GAME( 1995, doubledrncd,   doubledr,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Double Dragon (Japan, USA) (Neo-Geo)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, doubledrancd,  doubledr,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Double Dragon (Japan) (Neo-Geo)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, fatfurspncd,   fatfursp,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Fatal Fury Special / Garou Densetsu Special (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, fatfury1ncd,   fatfury1,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Fatal Fury - King of Fighters / Garou Densetsu - Shukumei no Tatakai (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, fatfury2ncd,   fatfury2,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Fatal Fury 2 / Garou Densetsu 2 - Arata-naru Tatakai (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, fatfury3ncd,   fatfury3,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Fatal Fury 3 - Road to the Final Victory / Garou Densetsu 3 - Haruka-naru Tatakai (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, fatfury3ancd,  fatfury3,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Fatal Fury 3 - Road to the Final Victory / Garou Densetsu 3 - Haruka-naru Tatakai (USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, fbfrenzyncd,   fbfrenzy,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Football Frenzy (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, froman2bncd,   froman2b,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Video System", "Idol Mahjong Final Romance 2 (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, galaxyfgncd,   galaxyfg,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Sunsoft", "Galaxy Fight - Universal Warriors (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, gowcaizrncd,   gowcaizr,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Technos Japan", "Voltage Fighter - Gowcaizer / Choujin Gakuen Gowcaizer (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, gpilotsncd,    gpilots,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Ghost Pilots (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ironcladncd,   ironclad,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Saurus", "Choutetsu Brikin'ger / Iron Clad (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, janshinncd,    janshin,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Aicom", "Janshin Densetsu - Quest of Jongmaster (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, joyjoyncd,     joyjoy,    neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Puzzled / Joy Joy Kid (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, kabukiklncd,   kabukikl,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Hudson", "Far East of Eden - Kabuki Klash / Tengai Makyou - Shin Den (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, karnovrncd,    karnovr,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Data East Corporation", "Karnov's Revenge / Fighter's History Dynamite (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, kof94ncd,      kof94,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '94 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, kof94ancd,     kof94,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '94 (Japan, USA, alt) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, kof95ncd,      kof95,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '95 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, kof95ancd,     kof95,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '95 (Japan, USA, alt) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, kof96ncd,      kof96,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '96 (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, kof96ancd,     kof96,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '96 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, kof96colncd,   kof96,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '96 NeoGeo Collection (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, kof97ncd,      kof97,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '97 (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, kof98ncd,      kof98,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - Dream Match Never Ends (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, kof99ncd,      kof99,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, kotm2ncd,      kotm2,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "King of the Monsters 2 - The Next Thing (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, lastbladncd,   lastblad,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The Last Blade / Bakumatsu Roman - Gekka no Kenshi (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, lastbld2ncd,   lastbld2,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The Last Blade 2 / Bakumatsu Roman - Dai Ni Maku Gekka no Kenshi (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 2007, lasthopencd,   lasthope,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "NG:DEV.TEAM", "Last Hope (Europe) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, lbowlingncd,   lbowling,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "League Bowling (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, looptrisncd,   looptris,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Blastar", "Looptris (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, looptrspncd,   looptris,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Blastar", "Looptris Plus (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, lresortncd,    lresort,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Last Resort (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, magdrop2ncd,   magdrop2,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Data East Corporation", "Magical Drop II (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, maglordncd,    maglord,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Magician Lord (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, mahretsuncd,   mahretsu,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Mahjong Kyo Retsuden (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, moshougincd,   moshougi,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Shougi no Tatsujin - Master of Shougi (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, mslugncd,      mslug,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Nazca", "Metal Slug - Super Vehicle-001 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, mslug2ncd,     mslug2,    neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Metal Slug 2 - Super Vehicle-001/II (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, mutnatncd,     mutnat,    neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Mutation Nation (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, nam1975ncd,    nam1975,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "NAM-1975 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, ncombatncd,    ncombat,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Ninja Combat (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, ncommandncd,   ncommand,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Ninja Commando (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, neodriftncd,   neodrift,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Visco", "Neo Drift Out - New Technology (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ngcdspecncd,    0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Neo Geo CD Special (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ninjamasncd,   ninjamas,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Ninja Master's - Haoh-ninpo-cho (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, overtopncd,    overtop,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Over Top (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, pbobblenncd,   pbobblen,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Taito", "Puzzle Bobble / Bust-A-Move (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, pgoalncdncd,   pgoal,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Saurus", "Pleasure Goal / Futsal - 5 on 5 Mini Soccer (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, pspikes2ncd,   pspikes2,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Video System Co.", "Power Spikes II (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, pulstarncd,    pulstar,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Aicom", "Pulstar (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, quizkofncd,    quizkof,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Saurus (SNK license)", "Quiz King of Fighters (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, ragnagrdncd,   ragnagrd,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Saurus", "Ragnagard / Shin-Oh-Ken (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, rbff1ncd,      rbff1,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Real Bout Fatal Fury / Real Bout Garou Densetsu (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, rbff2ncd,      rbff2,     neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Real Bout Fatal Fury 2 - The Newcomers / Real Bout Garou Densetsu 2 - The Newcomers (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, rbffspecncd,   rbffspec,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Real Bout Fatal Fury Special / Real Bout Garou Densetsu Special (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, ridheroncd,    ridhero,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Riding Hero (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, roboarmyncd,   roboarmy,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Robo Army (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, samshoncd,     samsho,    neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Samurai Shodown / Samurai Spirits (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, samsho2ncd,    samsho2,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Samurai Shodown II / Shin Samurai Spirits - Haohmaru Jigokuhen (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, samsho3ncd,    samsho3,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Samurai Shodown III / Samurai Spirits - Zankurou Musouken (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, samsho4ncd,    samsho4,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Samurai Shodown IV - Amakusa's Revenge / Samurai Spirits - Amakusa Kourin (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, samsprpgncd,    0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Shinsetsu Samurai Spirits - Bushidou Retsuden (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, savagerencd,   savagere,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Savage Reign / Fu'un Mokushiroku - Kakutou Sousei (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, sengokuncd,    sengoku,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Sengoku / Sengoku Denshou (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, sengoku2ncd,   sengoku2,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Sengoku 2 / Sengoku Denshou 2 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, socbrawlncd,   socbrawl,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Soccer Brawl (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, sonicwi2ncd,   sonicwi2,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Video System Co.", "Aero Fighters 2 / Sonic Wings 2 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, sonicwi3ncd,   sonicwi3,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Video System Co.", "Aero Fighters 3 / Sonic Wings 3 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, ssidekincd,    ssideki,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Super Sidekicks / Tokuten Ou (Japan, USA)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, ssideki2ncd,   ssideki2,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Super Sidekicks 2 - The World Championship / Tokuten Ou 2 - Real Fight Football (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, ssideki3ncd,   ssideki3,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Super Sidekicks 3 - The Next Glory / Tokuten Ou 3 - Eikou e no Chousen (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, stakwinncd,    stakwin,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Saurus", "Stakes Winner / Stakes Winner - GI Kinzen Seiha e no Michi (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, strhoopncd,    strhoop,   neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Data East Corporation", "Street Hoop / Street Slam / Dunk Dream (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, superspyncd,   superspy,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "The Super Spy (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, tophuntrncd,   tophuntr,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Top Hunter - Roddy & Cathy (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 2011, totcncd,       totc,      neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "FACE Corporation / N.C.I - Le Cortex", "Treasure Of The Caribbean (France) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, tpgolfncd,     tpgolf,    neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "SNK", "Top Player's Golf (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, trallyncd,     trally,    neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Thrash Rally (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, turfmastncd,   turfmast,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Nazca", "Neo Turf Masters / Big Tournament Golf (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1997, twinsprincd,   twinspri,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Twinkle Star Sprites (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, viewpoinncd,   viewpoin,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Sammy / Aicom", "Viewpoint (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, wh1ncd,        wh1,       neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "World Heroes (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, wh2ncd,        wh2,       neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "World Heroes 2 (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, wh2jncd,       wh2j,      neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "World Heroes 2 Jet (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1995, whpncd,        whp,       neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "World Heroes Perfect (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, wjammersncd,   wjammers,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Data East Corporation", "Windjammers / Flying Power Disc (Japan, USA) (Neo CD)", MACHINE_SUPPORTS_SAVE )
//GAME( 2019, xenoncd,       xeno,      neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Bitmap Bureau", "Xeno Crisis (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 1996, zintrckbncd,   zintrckb,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "ADK", "Zintrick / Oshidashi Zentrix (Japan) (Neo CD)", MACHINE_SUPPORTS_SAVE )

/*    YEAR  NAME           PARENT      MACHINE   INPUT   CLASS       INIT     MONITOR COMPANY  */
/* SNK HomeBrew */
GAME( 2016, alice_cd,       0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Blastar", "We Love Alice demo (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2024, chelnov_cd,     0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "iq_132", "Atomic Runner Chelnov (Neo-Geo port) (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, diff_cd,        0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Citavia", "DIFF demo (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2015, eira_cd,        0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Resistance", "Eira demo (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, ffury_cd,      fatfury1,  neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "[unk]", "Fatal Fury - King of Fighters / Garou Densetsu - Shukumei no Tatakai (Album Edition) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 2017, fukkireta_cd,   0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Visy", "Neo Fukkireta demo (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2025, gaxe_cd,        0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "h0ffman", "Golden Axe (Neo-Geo port) (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2025, gaxearr_cd,     0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "h0ffman", "Golden Axe (v1.0) (PS2 Sega Ages Arranged) (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, natademo_cd,    0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "BEY", "NATADEMO Rel.05 (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2011, ngdark_cd,      0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "NGD::Devgroup", "NGD::ARK (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2019, noneon_cd,      0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Citavia", "No Neo - No Party demo (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, ntris3d_cd,     0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Blastar", "N*tris3D Techdemo (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, phoenix_cd,     0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "BEY", "Phoenix(v013) (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2023, pong_cd,        0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "David Vandensteen", "Pong (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2025, pow_cd,         0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "iq_132", "P.O.W. (Neo-Geo port) (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2026, shinobiarr_cd,  0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "H0ffman", "Shinobi Arranged v1.1 (Neo-Geo port)[CD]", MACHINE_SUPPORTS_SAVE )
GAME( 2026, speedball_cd,   0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Z-team", "Speedball2 v1.0.0 demo (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, ssrpg_cd,    samsprpgncd, neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Apocalypse", "Shinsetsu Samurai Spirits - Bushidou Retsuden (English) (Neo CD)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, subspecies_cd,  0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Blastar", "Subspecies_Unfinished demo (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
GAME( 2016, visualnovel_cd, 0,        neocd_hb,  neocd, ngcd_hb,  init_neocdz,  ROT0, "Trilobit", "Visual Novel demo (Neo CD) (HB)", MACHINE_SUPPORTS_SAVE )
