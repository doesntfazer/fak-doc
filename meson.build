project('fak', 'c')

cc_args = ['--opt-code-size']
inc_dirs = ['src', 'src/inc']

sources_common = [
    'src/main.c',
    'src/time.c',
    'src/bootloader.c',
    'src/spi.c',
    'src/pmw3360.c',
]

sources_central = [
    'src/usb.c',
    'src/split_central.c',
    'src/keymap.c',
    'src/key_event_queue.c',
]

sources_peripheral = [
    'src/split_peripheral.c',
]

###

cc = find_program('sdcc', required : true)
nickel = find_program('nickel', required : true)
python = find_program('python', required : true)
wchisp = find_program('wchisp', required : false, disabler : true)

sides = ['central']
if get_option('split')
    sides += ['peripheral']
endif

foreach side : sides
    side_h = custom_target(side + '.h',
        input : 'fak.py',
        output : side + '.h',
        capture : true,
        command : [python, '@INPUT@', 'query_ncl', side + '.h'],
        depend_files : ['.eval.json'],
    )

    side_c = custom_target(side + '.c',
        input : 'fak.py',
        output : side + '.c',
        capture : true,
        command : [python, '@INPUT@', 'query_ncl', side + '.c'],
        depend_files : ['.eval.json'],
    )
endforeach
