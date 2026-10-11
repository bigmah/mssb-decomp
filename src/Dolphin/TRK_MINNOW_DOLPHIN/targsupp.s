.include "macros.inc"

# Debugger file-I/O hooks: each one traps into the attached debugger
# (twi 31 = unconditional trap), which services the request and returns.

.section .text, "ax"
.balign 16

.fn TRKAccessFile, global
	twi 31, r0, 0x0
	blr
.endfn TRKAccessFile

.fn TRKOpenFile, global
	twi 31, r0, 0x0
	blr
.endfn TRKOpenFile

.fn TRKCloseFile, global
	twi 31, r0, 0x0
	blr
.endfn TRKCloseFile

.fn TRKPositionFile, global
	twi 31, r0, 0x0
	blr
.endfn TRKPositionFile
