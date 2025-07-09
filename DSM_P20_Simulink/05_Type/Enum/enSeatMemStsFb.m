%% Create enSeatMemStsFb enum

classdef enSeatMemStsFb < Simulink.IntEnumType

    enumeration
        EN_FB_INACTIVE(0)
        EN_FB_CALL_MEM_POSI_SUCCEED(1)
        EN_FB_CALL_MEM_POSI_FAILD(2)
        EN_FB_WAITING(3)
        EN_FB_CLEAN_UP_MEM_POSI_SUCCEED(4)
        EN_FB_CLEAN_UP_MEM_POSI_FAILD(5)
        EN_FB_RESERVED(6)
        EN_FB_INVALID(7)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatMemStsFb.EN_FB_INACTIVE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '记忆调用反馈状态:&#10;0x0: Inactive&#10;0x1: Call Memory Position Succeed&#10;0x2: Call Memory Position Faild&#10;0x3: Waiting&#10;0x4: Clean Up Memory Position Succeed&#10;0x5: Clean Up Memory Position Faild&#10;0x6: Reserved&#10;0x7: Invalid,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
