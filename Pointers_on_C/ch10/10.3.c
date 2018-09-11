typedef union
{
	unsigned short addr;
	struct {
		unsigned opcode:10;
		unsigned dst_mode:3;
		unsigned dst_reg:3;
	} sql_op;
	struct {
		unsigned opcode:4;
		unsigned src_mode:3;
		unsigned src_reg:3;
		unsigned dst_mode:3;
		unsigned dst_reg:3;
	} dbl_op;
	struct {
		unsigned opcode:7;
		unsigned src_reg:3;
		unsigned dst_mode:3;
		unsigned dst_reg:3;
	} reg_src;
	struct {
		unsigned opcode:8;
		unsigned offset:8;
	} branch;
	struct {
		unsigned opcode:16;
	} misc;
}machine_inst;
