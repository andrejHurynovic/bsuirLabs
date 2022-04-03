onerror {quit -f}
vlib work
vlog -work work labwork3.vo
vlog -work work labwork3.vt
vsim -novopt -c -t 1ps -L cycloneiii_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.main_vlg_vec_tst
vcd file -direction labwork3.msim.vcd
vcd add -internal main_vlg_vec_tst/*
vcd add -internal main_vlg_vec_tst/i1/*
add wave /*
run -all
