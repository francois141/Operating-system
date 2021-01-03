
boot_message:
    db "Debut du chargement du systeme d'exploitation ",0
load_disk_message:
    db "Chargement du disque en cours",0
load_disk_sucess:
    db "Chargement du disque avec succes",0
load_disk_fail:
    db "Echec du chargement du disque",0
load_kernel_msg:
    db "Chargement du Kernel",0
load_32bit_mode:
    db "Chargement du mode 32 bits ",0
load_32bit_mode_success:
    db "Chargement du mode 32 bits réussi",0
test:
    db "Test ",0


BOOT_DRIVE : db 0