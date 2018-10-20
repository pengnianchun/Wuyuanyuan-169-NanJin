###########################################
# 该文件是生成最终的目标S19文件的编译工具
# 注意：1. 需要将CWS12v5.1 移动到C盘
#	2. 如果需要添加工程文件夹（不是文件）， 需要修改SRC_PATH
###########################################

#output
TARGET = $(BIN_PATH)/bingo.bin
TARGETS19 =  $(BIN_PATH)/bingom.s19

# the install dir of codewarrior 5.0 
#NOTE: 需要将安装包移动到C盘根目录 
CODRWARRIOR_DIR = C:/CWS12v5.1
COMPILER_DIR  = $(CODRWARRIOR_DIR)/Prog
PROJECT_DIR = .

#重要的链接文件
PRMFILE = $(PROJECT_DIR)/prm/Project.prm
BBLFILE = $(PROJECT_DIR)/prm/burner.bbl

OBJECTS_DIR = ./obj/

#common compilers
CC = $(COMPILER_DIR)/chc12.exe 
AS = $(COMPILER_DIR)/ahc12.exe
LD = $(COMPILER_DIR)/linker.exe
BURNER = $(COMPILER_DIR)/burner.exe
AR = ar
RM = rm

# common flags
# normal flags
NMFLGS = -WErrFileOff -WOutFileOff -MapFLASH -EnvOBJPATH=$(OBJECTS_DIR)

MACROS = -D__NO_FLOAT__ -D__MAP_FLASH__ 
ASFLGS = $(NMFLGS)  -Mb -CpuHCS12XE
#CFLAGS =  $(NMFLGS) $(MACROS) -Mb -CpuHCS12XE -Cc -DPPAGE_ADDR=0x15    -OnB=b  ##NOTE: 编译的时候会使用，注意参数。
CFLAGS = -Cc -CPUHCS12 -DPPAGE_ADDR=0x15 -D__NO_FLOAT__ -D__MAP_FLASH__ -Mb -MapFlash -OnB=b
#LDFLGS = -M -WmsgNu=abcet $(NMFLGS)
LDFLGS = -MapFlash
ARFLGS = rv
RMFLGS = -f



# obj
OBJ_PATH = obj
BIN_PATH = bin
SRC_PATH := \
           $(PROJECT_DIR)/Sources/User \
           $(PROJECT_DIR)/Sources \
           $(PROJECT_DIR)/Sources/font \
           $(PROJECT_DIR)/Sources/gui \
	   $(PROJECT_DIR)/Sources/can 
	   
SRC = $(CODRWARRIOR_DIR)/lib/hc12c/src/mc9s12g128.c 
SRC += ${PROJECT_DIR}/Sources/User/systermf.c \
       ${PROJECT_DIR}/Sources/User/SPI25LC1024.c \
       ${PROJECT_DIR}/Sources/User/str.c \
       ${PROJECT_DIR}/Sources/User/delay.c \
       ${PROJECT_DIR}/Sources/User/key.c \
       ${PROJECT_DIR}/Sources/User/bmp.c \
       ${PROJECT_DIR}/Sources/User/global.c \
       ${PROJECT_DIR}/Sources/User/fault.c \
       ${PROJECT_DIR}/Sources/fault_page.c \
       ${PROJECT_DIR}/Sources/datapage.c \
       ${PROJECT_DIR}/Sources/MCUinit.c \
       ${PROJECT_DIR}/Sources/main.c \
       ${PROJECT_DIR}/Sources/Start12.c \
       ${PROJECT_DIR}/Sources/stepper.c \
       ${PROJECT_DIR}/Sources/panel.c \
       ${PROJECT_DIR}/Sources/font/show_string.c \
       ${PROJECT_DIR}/Sources/font/zh_font.c \
       ${PROJECT_DIR}/Sources/gui/batteryManager_page.c \
       ${PROJECT_DIR}/Sources/gui/air_page.c \
       ${PROJECT_DIR}/Sources/gui/control_page.c \
       ${PROJECT_DIR}/Sources/gui/gui.c \
       ${PROJECT_DIR}/Sources/gui/debug_page.c \
       ${PROJECT_DIR}/Sources/gui/main_page.c \
       ${PROJECT_DIR}/Sources/gui/menu_page.c \
       ${PROJECT_DIR}/Sources/gui/ILI9481.c \
       ${PROJECT_DIR}/Sources/gui/show.c \
       ${PROJECT_DIR}/Sources/gui/auxiliary_page.c \
       ${PROJECT_DIR}/Sources/can/can.c \
       ${PROJECT_DIR}/Sources/can/can_msg_handle.c 

#SRC += $(foreach x,$(SRC_PATH),$(wildcard $(addprefix $(x)/*,.c .S)))            ##这个是所有的.c

OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .c.o,$(notdir $(basename $(SRC)))))  ##这个是所有的.o
LIBS = $(CODRWARRIOR_DIR)/lib/hc12c/lib/ansibi.lib


#OBJ += $(OBJECTS_DIR)/mc9s12g128.c.o

INCDIR = $(CODRWARRIOR_DIR)/lib/hc12c/include $(SRC_PATH)
# 确定环境变量
VPATH = $(INCDIR) $(CODRWARRIOR_DIR)/lib/hc12c/src/

.PHONY: all sim clean compiler 


all: start $(OBJ) end_build linking $(TARGETS19) end_linking done

###规则
$(OBJ_PATH)/%.c.o : %.c
	@echo "  >>  $@ $^"
	@mkdir -p ${OBJ_PATH}
	$(CC) -F2 $(CFLAGS) -ObjN=$@  $(addprefix -I,$(INCDIR))  $^ 


$(TARGET): $(OBJ)
	@echo "  >> LD $@ Link_Object : $(OBJ)"
	$(LD) $(PRMFILE) $(LDFLGS) -Add{$(LIBS)} -Add{$(OBJ)} -O$(TARGET)

$(TARGETS19) : $(TARGET)
	$(BURNER)  -Env"ABS_FILE=$(TARGET)" -f $(BBLFILE)

clean : 
	rm -f $(TARGETS19) $(TARGET)
	rm -f $(OBJ_PATH)/*.o

##仅仅是进度
start :
	@echo "---------------------- start of compilation ----------------------------"

end_build :
	@echo "---------------------- end of compilation  -----------------------------"
linking :
	@echo "---------------------- start of linkprocess ----------------------------"
end_linking :
	@echo "----------------------  end of linkprocess  ----------------------------"
done:
	@echo
	@echo "  >>>>>>>  DONE  !!!<<<<<<<<<"
	@echo
