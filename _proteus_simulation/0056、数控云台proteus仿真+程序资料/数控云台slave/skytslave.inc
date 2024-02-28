	.DEF _rx_wr_index=R4
	.DEF _rx_rd_index=R5
	.DEF _rx_counter=R6
	.DEF _tx_wr_index=R7
	.DEF _tx_rd_index=R8
	.DEF _tx_counter=R9
	.DEF _ucInputValue=R10
	.DEF _ucInputParam0=R11
	.DEF _ucChannelN=R12
	.DEF _uc_ReceiveSta=R13
_109:
	.DB  0x6F,0x6B,0x0
_tbl10_G3:
	.DW  0x2710,0x3E8,0x64,0xA,0x1
_tbl16_G3:
	.DW  0x1000,0x100,0x10,0x1

__GLOBAL_INI_TBL:
	.DW  0
