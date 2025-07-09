%% Create enSeatMemBtnCmd enum

classdef enSeatMemBtnCmd < Simulink.IntEnumType

    enumeration
        EN_NULL(0)
        EN_MEM_BTN1(1)
        EN_CALL_BTN1(2)
        EN_CLEAN_BTN1(3)
        EN_MEM_BTN2(4)
        EN_CALL_BTN2(5)
        EN_CLEAN_BTN2(6)
        EN_MEM_BTN3(7)
        EN_CALL_BTN3(8)
        EN_CLEAN_BTN3(9)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatMemBtnCmd.EN_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '记忆报文处理:&#10;0：NULL（无）&#10;1:MemorizeButton1&#10;2:CallButton1&#10;3:CLeanButton1&#10;4:MemorizeButton2&#10;5:CallButton2&#10;6:CLeanButton2&#10;7:MemorizeButton3&#10;8:CallButton3&#10;9:CLeanButton3,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
