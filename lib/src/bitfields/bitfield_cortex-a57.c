#include <stdio.h>
#include <sys/ioctl.h>

#include "maplesyrup.h"
#include "parse.h"
#include "bitfield_cortex-a57.h"

bitfield_info bitfield_cortex_a57_table[] =
{   
    { 1, 0, MS_SYSREG_MPIDR, NS_PRIVILEGE_LEVEL_1, 0, 2, "CPU ID", "ident", "MPIDR", "Core number of Cortex-A57 processor" },
    { 1, 1, MS_SYSREG_MPIDR, NS_PRIVILEGE_LEVEL_1, 2, 6, "Reserved", "ident", "MPIDR", "Reserved" },
    { 1, 2, MS_SYSREG_MPIDR, NS_PRIVILEGE_LEVEL_1, 8, 8, "Cluster ID Aff1", "ident", "MPIDR", "Affinity level 1" },
    { 1, 3, MS_SYSREG_MPIDR, NS_PRIVILEGE_LEVEL_1, 16, 8, "Cluster ID Aff2", "ident", "MPIDR", "Affinity level 2" },
    { 1, 4, MS_SYSREG_MPIDR, NS_PRIVILEGE_LEVEL_1, 24, 1, "MT", "ident", "MPIDR", "Lowest affinity cores are multi-threaded" },
    { 1, 5, MS_SYSREG_MPIDR, NS_PRIVILEGE_LEVEL_1, 25, 5, "Reserved", "ident", "MPIDR", "Reserved" },
    { 1, 6, MS_SYSREG_MPIDR, NS_PRIVILEGE_LEVEL_1, 30, 1, "U", "ident", "MPIDR", "Indicates a single core system" },
    { 1, 7, MS_SYSREG_MPIDR, NS_PRIVILEGE_LEVEL_1, 31, 1, "Reserved", "ident", "MPIDR", "Reserved" },
    { 1, 8, MS_SYSREG_MPIDR, NS_PRIVILEGE_LEVEL_1, 32, 32, "Reserved", "ident", "MPIDR", "Reserved" },  
    
    { 1, 0, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 0, 1, "M", "virtmem", "SCTLR", "MMU Enable" },
    { 1, 1, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 1, 1, "A", "virtmem", "SCTLR", "Alignment check enable" },
    { 1, 2, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 2, 1, "C", "virtmem", "SCTLR", "Cache enable" },
    { 1, 3, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 3, 1, "SA", "virtmem", "SCTLR", "Stack alignment check enable" },
    { 1, 4, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 4, 1, "SA0", "virtmem", "SCTLR", "Stack alignment check enable for EL0" },
    { 1, 5, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 5, 1, "CP15BEN", "virtmem", "SCTLR", "CP15 barrier enable" },
    { 1, 6, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 6, 1, "THEE", "virtmem", "SCTLR", "T32EE not implemented" },
    { 1, 7, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 7, 1, "ITD", "virtmem", "SCTLR", "Disables some uses of IT instructions at EL0 using AArch32" },
    { 1, 8, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 8, 1, "SED", "virtmem", "SCTLR", "Disables the SETEND instruction at EL0 using AArch32" },
    { 1, 9, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 9, 1, "UMA", "virtmem", "SCTLR", "Traps EL0 execution of MSR and MRS instructions that access PSTATE" },
    { 1, 10, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 10, 1, "Reserved", "virtmem", "SCTLR", "Reserved" },
    { 1, 11, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 11, 1, "Reserved", "virtmem", "SCTLR", "Reserved" },
    { 1, 12, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 12, 1, "I", "virtmem", "SCTLR", "Instruction access Cacheability control" },
    { 1, 13, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 13, 1, "Reserved", "virtmem", "SCTLR", "Reserved" },
    { 1, 14, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 14, 1, "DZE", "virtmem", "SCTLR", "Traps EL0 execution of DC ZVA instructions to EL1" },
    { 1, 15, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 15, 1, "UCT", "virtmem", "SCTLR", "Traps EL0 access to the CTR_EL0 register to EL1" },
    { 1, 16, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 16, 1, "NTWI", "virtmem", "SCTLR", "Traps EL0 execution of WFI instructions to EL1" },
    { 1, 17, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 17, 1, "Reserved", "virtmem", "SCTLR", "Reserved" },
    { 1, 18, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 18, 1, "NTWE", "virtmem", "SCTLR", "Traps EL0 execution of WFE instructions to EL1" },
    { 1, 19, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 19, 1, "WXN", "virtmem", "SCTLR", "Write permission implies XN (Execute Never) at EL0/1" },
    { 1, 20, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 20, 1, "Reserved", "virtmem", "SCTLR", "Reserved" },
    { 1, 21, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 21, 1, "Reserved", "virtmem", "SCTLR", "Reserved" },
    { 1, 22, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 22, 2, "Reserved", "virtmem", "SCTLR", "Reserved" },
    { 1, 23, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 24, 1, "E0E", "virtmem", "SCTLR", "Endianess of data access at EL0" },
    { 1, 24, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 25, 1, "EE", "virtmem", "SCTLR", "Endianess of data at EL1 and translation table walk" },
    { 1, 25, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 26, 1, "UCI", "virtmem", "SCTLR", "Traps EL0 cache maintenance instructions to EL1" },
    { 1, 26, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 27, 1, "Reserved", "virtmem", "SCTLR", "Reserved" },
    { 1, 27, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 28, 2, "Reserved", "virtmem", "SCTLR", "Reserved" },
    { 1, 28, MS_SYSREG_SCTLR, NS_PRIVILEGE_LEVEL_1, 30, 2, "Reserved", "virtmem", "SCTLR", "Reserved" },
    
    { 1, 0, MS_SYSREG_TTBR0, NS_PRIVILEGE_LEVEL_1, 0, 10, "Reserved", "virtmem", "TTBR0", "Reserved" },
    { 1, 1, MS_SYSREG_TTBR0, NS_PRIVILEGE_LEVEL_1, 10, 38, "BADDR", "virtmem", "TTBR0", "Translation table base address" },
    { 1, 2, MS_SYSREG_TTBR0, NS_PRIVILEGE_LEVEL_1, 48, 16, "ASID", "virtmem", "TTBR0", "ASID for translation table base address" },
    
    { 1, 0, MS_SYSREG_TTBR1, NS_PRIVILEGE_LEVEL_1, 0, 10, "Reserved", "virtmem", "TTBR1", "Reserved" },
    { 1, 1, MS_SYSREG_TTBR1, NS_PRIVILEGE_LEVEL_1, 10, 38, "BADDR", "virtmem", "TTBR1", "Translation table base address" },
    { 1, 2, MS_SYSREG_TTBR1, NS_PRIVILEGE_LEVEL_1, 48, 16, "ASID", "virtmem", "TTBR1", "ASID for translation table base address" },
    
    { 1, 0, MS_SYSREG_DFSR, NS_PRIVILEGE_LEVEL_1, 0, 6, "IFSC", "fault", "ESR", "Instruction Fault Status Code" },
    { 1, 1, MS_SYSREG_DFSR, NS_PRIVILEGE_LEVEL_1, 6, 1, "Reserved", "fault", "ESR", "Reserved" },
    { 1, 2, MS_SYSREG_DFSR, NS_PRIVILEGE_LEVEL_1, 7, 1, "S1PTW", "fault", "ESR", "Indicates instruction fault from translation table walk" },
    { 1, 3, MS_SYSREG_DFSR, NS_PRIVILEGE_LEVEL_1, 8, 1, "Reserved", "fault", "ESR", "Reserved" },
    { 1, 4, MS_SYSREG_DFSR, NS_PRIVILEGE_LEVEL_1, 9, 1, "EA", "fault", "ESR", "External abort type" },
    { 1, 5, MS_SYSREG_DFSR, NS_PRIVILEGE_LEVEL_1, 10, 15, "Reserved", "fault", "ESR", "Reserved" },
    { 1, 6, MS_SYSREG_DFSR, NS_PRIVILEGE_LEVEL_1, 25, 1, "IL", "fault", "ESR", "Instruction length for synchronous exceptions" },
    { 1, 7, MS_SYSREG_DFSR, NS_PRIVILEGE_LEVEL_1, 26, 6, "EC", "fault", "ESR", "Exception class" },

    { 1, 0, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 0, 1, "D", "addrtrans", "PAR", "Indicates successful conversion" },
    { 1, 1, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 1, 6, "Reserved", "addrtrans", "PAR", "Reserved" },
    { 1, 2, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 7, 2, "SHA", "addrtrans", "PAR", "Shareability attribute" },
    { 1, 3, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 9, 1, "NS", "addrtrans", "PAR", "Non-secure" },
    { 1, 4, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 10, 1, "Reserved", "addrtrans", "PAR", "Reserved" },
    { 1, 5, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 11, 1, "Reserved", "addrtrans", "PAR", "Reserved" },
    { 1, 6, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 12, 36, "PA", "addrtrans", "PAR", "Physical address" },
    { 1, 7, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 48, 8, "Reserved", "addrtrans", "PAR", "Reserved" },
    { 1, 8, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 56, 4, "AttrL", "addrtrans", "PAR", "Defines device memory and inner cacheability" },
    { 1, 9, MS_SYSREG_PAR, NS_PRIVILEGE_LEVEL_1, 60, 4, "AttrH", "addrtrans", "PAR", "Defined normal and device memory and outer cacheability" },

    { 1, 0, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 0, 3, "DATALATENCY", "impl_def", "L2CTLR", "L2 Data RAM latency" },
    { 1, 1, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 3, 2, "Reserved", "impl_def", "L2CTLR", "Reserved" },
    { 1, 2, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 5, 1, "DATASETUP", "impl_def", "L2CTLR", "L2 Data RAM setup" },
    { 1, 3, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 6, 3, "L2 Tag RAM latency", "impl_def", "L2CTLR", "L2 Tag RAM latency" },
    { 1, 4, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 9, 1, "TAGSETUP", "impl_def", "L2CTLR", "L2 Tag RAM setup" },
    { 1, 5, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 10, 2, "DATASLICE", "impl_def", "L2CTLR", "L2 Data RAM slice" },
    { 1, 6, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 12, 1, "TAGSLICE", "impl_def", "L2CTLR", "L2 Tag RAM slice" },
    { 1, 7, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 13, 1, "ARBSLICE", "impl_def", "L2CTLR", "L2 arbitration slice" },
    { 1, 8, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 14, 6, "Reserved", "impl_def", "L2CTLR", "Reserved" },
    { 1, 9, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 20, 1, "DIECCE", "impl_def", "L2CTLR", "Data inline ECC enable" },
    { 1, 10, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 21, 1, "ECCPE", "impl_def", "L2CTLR", "ECC and parity enable" },
    { 1, 11, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 22, 1, "L1CPE", "impl_def", "L2CTLR", "L1 cache ECC and parity protection" },
    { 1, 12, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 23, 1, "Reserved", "impl_def", "L2CTLR", "Reserved" },
    { 1, 13, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 24, 2, "Number of processors", "impl_def", "L2CTLR", "Number of processors" },
    { 1, 14, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 26, 5, "Reserved", "impl_def", "L2CTLR", "Reserved" },
    { 1, 15, MS_SYSREG_L2CTLR, NS_PRIVILEGE_LEVEL_1, 31, 1, "L2RSTDISABLE monitor", "impl_def", "L2CTLR", "Monitors the L2 hardware reset disable signal" },
    
    { 1, 0, MS_SYSREG_L2ECTLR, NS_PRIVILEGE_LEVEL_1, 0, 3, "DYNRET", "impl_def", "L2ECTLR", "L2 dynamic retention control" },
    { 1, 1, MS_SYSREG_L2ECTLR, NS_PRIVILEGE_LEVEL_1, 3, 26, "Reserved", "impl_def", "L2ECTLR", "Reserved" },
    { 1, 2, MS_SYSREG_L2ECTLR, NS_PRIVILEGE_LEVEL_1, 29, 1, "ASYNCERR", "impl_def", "L2ECTLR", "ACI or AMBA 5 CHI asynchronous error" },
    { 1, 3, MS_SYSREG_L2ECTLR, NS_PRIVILEGE_LEVEL_1, 30, 1, "IASYNCERR", "impl_def", "L2ECTLR", "L2 internal asynchronous error" },
    { 1, 4, MS_SYSREG_L2ECTLR, NS_PRIVILEGE_LEVEL_1, 31, 1, "IASYNCERR", "impl_def", "L2ECTLR", "L2 internal asynchronous error" },
    
    { 1, 0, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 0, 1, "DHPF", "impl_def", "L2ACTLR", "Disable hardware prefetch foward" },
    { 1, 1, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 1, 1, "EARTT", "impl_def", "L2ACTLR", "Enable arbitration replay threshold limit" },
    { 1, 2, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 2, 1, "LTORPTB", "impl_def", "L2ACTLR", "Limit to one request per tag bank" },
    { 1, 3, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 3, 1, "DCEPTE", "impl_def", "L2ACTLR", "Disable clean/evict push to external" },
    { 1, 4, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 4, 1, "DWWTFM", "impl_def", "L2ACTLR", "Disable WriteUnique and WriteLineUnique transactions from master" },
    { 1, 5, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 5, 1, "Reserved", "impl_def", "L2ACTLR", "Reserved" },
    { 1, 6, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 6, 1, "DACE", "impl_def", "L2ACTLR", "Disable ACE shareable or CHI snoopable transactions from master" },
    { 1, 7, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 7, 1, "EHDT", "impl_def", "L2ACTLR", "Enable hazard-detect timeout" },
    { 1, 8, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 8, 1, "DMB", "impl_def", "L2ACTLR", "Disable DVM/CMO message broadcast" },
    { 1, 9, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 9, 1, "Reserved", "impl_def", "L2ACTLR", "Reserved" },
    { 1, 10, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 10, 1, "DNSDAA", "impl_def", "L2ACTLR", "Disable Non-secure debug array access" },
    { 1, 11, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 11, 1, "DDSB", "impl_def", "L2ACTLR", "Disable DSB with no DVM-sync" },
    { 1, 12, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 12, 1, "Reserved", "impl_def", "L2ACTLR", "Reserved" },
    { 1, 13, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 13, 1, "DCEO", "impl_def", "L2ACTLR", "Disable clean/evict optimization" },
    { 1, 14, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 14, 1, "EUED", "impl_def", "L2ACTLR", "Enable UniqueClean evictions with data" },
    { 1, 15, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 15, 1, "DFF", "impl_def", "L2ACTLR", "Disable fast fowarding of data from ACE or CHI to LS and IF" },
    { 1, 16, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 16, 1, "ERTSI", "impl_def", "L2ACTLR", "Enable replay threshold single issue" },
    { 1, 17, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 17, 1, "DL2RR", "impl_def", "L2ACTLR", "Disable L2 round-robin arbitration that only clocks through paths with an active requester waiting to be arbitrated" },
    { 1, 18, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 18, 2, "DLASQ", "impl_def", "L2ACTLR", "Disable limit on NC/SO/Dev stores in Address Sequence Queue" },
    { 1, 19, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 20, 2, "DTL2PR", "impl_def", "L2ACTLR", "Disable throttling of L2 prefetch requests based on Fill/Evict Queue occupancy count" },
    { 1, 20, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 22, 1, "DDTPR", "impl_def", "L2ACTLR", "Disable dynamic throttling of LS prefetch requests" },
    { 1, 21, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 23, 1, "DPFR", "impl_def", "L2ACTLR", "Disable PF requests from ReadUnique transactions" },
    { 1, 22, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 24, 1, "Reserved", "impl_def", "L2ACTLR", "Reserved" },
    { 1, 23, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 25, 1, "ESIAL", "impl_def", "L2ACTLR", "Enable single issue across all tag banks when L2 arbitration replay threshold is reached" },
    { 1, 24, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 26, 1, "FL2", "impl_def", "L2ACTLR", "Force L2, GIC, Timer RCG enables active" },
    { 1, 25, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 27, 1, "FL2LC", "impl_def", "L2ACTLR", "Force L2 logic clock enable active" }, 
    { 1, 26, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 28, 1, "FL2LC", "impl_def", "L2ACTLR", "Force L2 tag banks clock enable active" }, 
    { 1, 27, MS_SYSREG_L2ACTLR, NS_PRIVILEGE_LEVEL_1, 29, 3, "Reserved", "impl_def", "L2ACTLR", "Reserved" },  
    
    { 1, 0, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 0, 1, "BTB", "impl_def", "CPUACTLR", "Enables invalidates of BTB" },
    { 1, 1, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 1, 1, "DICMS", "impl_def", "CPUACTLR", "Disable instruction cache miss streaming" },
    { 1, 2, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 2, 1, "Reserved", "impl_def", "CPUACTLR", "Reserved" },
    { 1, 3, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 3, 1, "DMBTB", "impl_def", "CPUACTLR", "Disables micro-Branch Target Buffer" },
    { 1, 4, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 4, 1, "DIP", "impl_def", "CPUACTLR", "Disable interrupt predictor" },
    { 1, 5, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 5, 1, "EPLDNOP", "impl_def", "CPUACTLR", "Execute PLD instruction as a NOP" },
    { 1, 6, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 6, 1, "Reserved", "impl_def", "CPUACTLR", "Reserved" },
    { 1, 7, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 7, 1, "EWFENOP", "impl_def", "CPUACTLR", "Executes WFE instruction as a NOP instruction" },
    { 1, 8, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 8, 1, "EWFINOP", "impl_def", "CPUACTLR", "Executes WFI instruction as a NOP instruction" },
    { 1, 9, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 9, 1, "DFRO", "impl_def", "CPUACTLR", "Disable flag renaming optimization" },
    { 1, 10, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 10, 1, "FS", "impl_def", "CPUACTLR", "Force serialization after each instruction group" },
    { 1, 11, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 11, 1, "L1PIG", "impl_def", "CPUACTLR", "Limit to one instruction per instruction group" },
    { 1, 12, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 12, 1, "FPCP", "impl_def", "CPUACTLR", "Forces push of certain SPRs from local dispatch copies to shadow copies" },
    { 1, 13, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 13, 1, "FLCP", "impl_def", "CPUACTLR", "Flush after certain SPR writes" },
    { 1, 14, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 14, 1, "FL", "impl_def", "CPUACTLR", "Force limit of one instruction group commit/deallocate per cycle" },
    { 1, 15, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 15, 1, "FIOBEU", "impl_def", "CPUACTLR", "Force in-order issue in branch execution unit" },
    { 1, 16, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 16, 1, "EFSO", "impl_def", "CPUACTLR", "Enable full strongly-ordered and device load replay" },
    { 1, 17, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 17, 1, "DL2_01", "impl_def", "CPUACTLR", "Disables L2 TLB performance optimizations" }, 
    { 1, 18, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 18, 1, "DL2_02", "impl_def", "CPUACTLR", "Disables L2 stage 1 translation table walk L2 PA cache" },
    { 1, 19, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 19, 1, "DL2_03", "impl_def", "CPUACTLR", "Disable L2 stage 1 translation table walk cache" },
    { 1, 20, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 20, 1, "DL2_04", "impl_def", "CPUACTLR", "Disable L2 translation table walk IPA PA cache" },
    { 1, 21, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 21, 1, "DL2_05", "impl_def", "CPUACTLR", "Disable L2 TLB prefetching" },
    { 1, 22, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 22, 1, "FIOL", "impl_def", "CPUACTLR", "Force in-order load issue" }, 
    { 1, 23, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 23, 1, "FIOR", "impl_def", "CPUACTLR", "Force in-order requests to the same set and way" },
    { 1, 24, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 24, 1, "NCSE", "impl_def", "CPUACTLR", "Non-cacheable streaming enhancement" },
    { 1, 25, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 25, 2, "WSL1T", "impl_def", "CPUACTLR", "Write streaming no L1-allocate threshold" },
    { 1, 26, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 27, 2, "WSNAT", "impl_def", "CPUACTLR", "Write streaming no allocate threshold" },
    { 1, 27, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 29, 1, "FNCEA", "impl_def", "CPUACTLR", "Force Advanced SIMD and Floating-point clock enable active" },
    { 1, 28, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 30, 1, "FMCEA", "impl_def", "CPUACTLR", "Force main clock enable active" },
    { 1, 29, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 31, 1, "SDEH", "impl_def", "CPUACTLR", "Snoop-delayed exclusive handling" },      
    { 1, 30, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 32, 1, "DICP", "impl_def", "CPUACTLR", "Disable instruction cache prefetch" },
    { 1, 31, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 33, 1, "DICW", "impl_def", "CPUACTLR", "Disable instruction Cache way" },
    { 1, 32, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 34, 1, "DSBP", "impl_def", "CPUACTLR", "Disable static branch predictor" },
    { 1, 33, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 35, 1, "Reserved", "impl_def", "CPUACTLR", "Reserved" },
    { 1, 34, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 36, 1, "FIDSB", "impl_def", "CPUACTLR", "Force implicit DSB on an ISB" },
    { 1, 35, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 37, 1, "DIGS", "impl_def", "CPUACTLR", "Disable instruction group split" },
    { 1, 36, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 38, 1, "FFWF", "impl_def", "CPUACTLR", "Force FPSCR write flush" },
    { 1, 37, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 39, 1, "DIM", "impl_def", "CPUACTLR", "Disable instruction merging" },
    { 1, 38, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 40, 4, "Reserved", "impl_def", "CPUACTLR", "Reserved" },
    { 1, 39, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 44, 1, "EDC", "impl_def", "CPUACTLR", "Execute Data Cache clean as Data Cache clean/invalidate" },
    { 1, 40, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 45, 2, "Reserved", "impl_def", "CPUACTLR", "Reserved" },
    { 1, 41, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 47, 1, "DDSIDE", "impl_def", "CPUACTLR", "Disable D-side L1/L2 hardware prefetch across 4KB page boundary even if page is 64KB or larger" },
    { 1, 42, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 48, 1, "DESRA", "impl_def", "CPUACTLR", "Disable early speculative read access from LS to L2" },
    { 1, 43, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 49, 1, "DNAH", "impl_def", "CPUACTLR", "Disable non-allocate hint of Write-Back No-Allocate memory type" },
    { 1, 44, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 50, 1, "DSS", "impl_def", "CPUACTLR", "Disable store streaming on NC/GRE memory type" },
    { 1, 45, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 51, 1, "DCD", "impl_def", "CPUACTLR", "Disable contention detection and fast exclusive monitor path" },
    { 1, 46, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 52, 1, "DOR", "impl_def", "CPUACTLR", "Disable over-read from LDNP instruction" },
    { 1, 47, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 53, 1, "TDMB", "impl_def", "CPUACTLR", "Treat DMB/DSB as if their domain field is SY" },
    { 1, 48, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 54, 1, "TGRE", "impl_def", "CPUACTLR", "Tread GRE/nGRE as nGnRE" },
    { 1, 49, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 55, 1, "DLPS", "impl_def", "CPUACTLR", "Disable load pass store" },
    { 1, 50, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 56, 1, "DL1HP", "impl_def", "CPUACTLR", "Disable L1 hardware prefetcher" },
    { 1, 51, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 57, 1, "TDMBA", "impl_def", "CPUACTLR", "Treat DMB st/st and ld/all as DMB all/all" },
    { 1, 52, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 58, 1, "DDMBN", "impl_def", "CPUACTLR", "Disable DMB nullification" },
    { 1, 53, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 59, 1, "DLPDMB", "impl_def", "CPUACTLR", "Disable load pass DMB" },
    { 1, 54, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 60, 3, "Reserved", "impl_def", "CPUACTLR", "Reserved" },
    { 1, 55, MS_SYSREG_CPUACTLR, NS_PRIVILEGE_LEVEL_1, 63, 1, "FPRCG", "impl_def", "CPUACTLR", "Force processor RCG enables active" },

    { 1, 0, MS_SYSREG_CPUMERRSR, NS_PRIVILEGE_LEVEL_1, 0, 18, "RAMADDR", "impl_def", "CPUMERRSR", "Indicates the index address of the first memory error" },  
    { 1, 1, MS_SYSREG_CPUMERRSR, NS_PRIVILEGE_LEVEL_1, 18, 5, "CPUIDWAY", "impl_def", "CPUMERRSR", "Indicates the RAM where the first memory error occurred" }, 
    { 1, 2, MS_SYSREG_CPUMERRSR, NS_PRIVILEGE_LEVEL_1, 23, 1, "Reserved", "impl_def", "CPUMERRSR", "Reserved" },    
    { 1, 3, MS_SYSREG_CPUMERRSR, NS_PRIVILEGE_LEVEL_1, 24, 7, "RAMID", "impl_def", "CPUMERRSR", "Ram Identifier" },
    { 1, 4, MS_SYSREG_CPUMERRSR, NS_PRIVILEGE_LEVEL_1, 31, 1, "Valid", "impl_def", "CPUMERRSR", "Valid bit. Set to 1 on first memory error" },
    { 1, 5, MS_SYSREG_CPUMERRSR, NS_PRIVILEGE_LEVEL_1, 32, 8, "REC", "impl_def", "CPUMERRSR", "Repeat memory error count when valid bit is set" },
    { 1, 6, MS_SYSREG_CPUMERRSR, NS_PRIVILEGE_LEVEL_1, 40, 8, "OEC", "impl_def", "CPUMERRSR", "Other memory error count when valid bit is set" },
    { 1, 7, MS_SYSREG_CPUMERRSR, NS_PRIVILEGE_LEVEL_1, 48, 15, "Reserved", "impl_def", "CPUMERRSR", "Reserved" },
    { 1, 8, MS_SYSREG_CPUMERRSR, NS_PRIVILEGE_LEVEL_1, 63, 1, "Fatal", "impl_def", "CPUMERRSR", "Fatal bit. Set to 1 on first memory error that cased data abort" },

    { 1, 0, MS_SYSREG_L2MERRSR, NS_PRIVILEGE_LEVEL_1, 0, 18, "Reserved", "impl_def", "L2MERRSR", "Reserved" },
    { 1, 1, MS_SYSREG_L2MERRSR, NS_PRIVILEGE_LEVEL_1, 18, 4, "CPUIDWAY", "impl_def", "L2MERRSR", "Indicates the RAM where the first memory error occurred" },   
    { 1, 2, MS_SYSREG_L2MERRSR, NS_PRIVILEGE_LEVEL_1, 22, 2, "Reserved", "impl_def", "L2MERRSR", "Reserved" },
    { 1, 3, MS_SYSREG_L2MERRSR, NS_PRIVILEGE_LEVEL_1, 24, 7, "RAMID", "impl_def", "L2MERRSR", "Indicates the RAM where the first memory error occurred" }, 
    { 1, 4, MS_SYSREG_L2MERRSR, NS_PRIVILEGE_LEVEL_1, 31, 1, "VALID", "impl_def", "L2MERRSR", "Valid bit. Set to 1 on first memory error" },
    { 1, 5, MS_SYSREG_L2MERRSR, NS_PRIVILEGE_LEVEL_1, 32, 8, "REC", "impl_def", "L2MERRSR", "Repeat memory error count when valid bit is set" },
    { 1, 6, MS_SYSREG_L2MERRSR, NS_PRIVILEGE_LEVEL_1, 40, 8, "OEC", "impl_def", "L2MERRSR", "Other memory error count when valid bit is set" },
    { 1, 7, MS_SYSREG_L2MERRSR, NS_PRIVILEGE_LEVEL_1, 48, 15, "Reserved", "impl_def", "L2MERRSR", "Reserved" },
    { 1, 8, MS_SYSREG_L2MERRSR, NS_PRIVILEGE_LEVEL_1, 63, 1, "Fatal", "impl_def", "L2MERRSR", "Fatal bit. Set to 1 on first memory error that cased data abort" },

    { 1, 0, MS_SYSREG_CBAR, NS_PRIVILEGE_LEVEL_1, 0, 18, "Reserved", "impl_def", "CBAR", "Reserved" },
    { 1, 1, MS_SYSREG_CBAR, NS_PRIVILEGE_LEVEL_1, 18, 32, "PERIPHBASE", "impl_def", "CBAR", "Reset base address of memory-mapped GIC CPU interface registers" },
    { 1, 2, MS_SYSREG_CBAR, NS_PRIVILEGE_LEVEL_1, 40, 24, "Reserved", "impl_def", "CBAR", "Reserved" },

    { 1, 0, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 0, 3, "PDRC", "impl_def", "CPUECTLR", "Process dynamic retention control" },
    { 1, 1, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 3, 3, "Reserved", "impl_def", "CPUECTLR", "Reserved" },
    { 1, 2, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 6, 1, "SMPEN", "impl_def", "CPUECTLR", "Enable processor to receive instruction cache and TLB maintenance operations broadcast from other processors in the cluster" },
    { 1, 3, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 7, 25, "Reserved", "impl_def", "CPUECTLR", "Reserved" },
    { 1, 4, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 32, 2, "L2IFPD", "impl_def", "CPUECTLR", "Indicates the L2 load/store data prefetch distance" },
    { 1, 5, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 34, 1, "Reserved", "impl_def", "CPUECTLR", "Reserved" },
    { 1, 6, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 35, 2, "L2LSDPD", "impl_def", "CPUECTLR", "Indicates the L2 instruction fetch prefetch distance" },
    { 1, 7, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 37, 1, "Reserved", "impl_def", "CPUECTLR", "Reserved" },
    { 1, 8, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 38, 1, "DTWDAP", "impl_def", "CPUECTLR", "Disable table walk descriptor access prefetch" },
    { 1, 9, MS_SYSREG_CPUECTLR, NS_PRIVILEGE_LEVEL_1, 39, 25, "Reserved", "impl_def", "CPUECTLR", "Reserved" },

};

int
return_bitfield_cortex_a57_size(void)
{
    return (sizeof(bitfield_cortex_a57_table) / sizeof(bitfield_info));
}
