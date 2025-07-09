%% Create enMemCallFb enum

classdef enMemCallFb < Simulink.IntEnumType

    enumeration
        EN_MemCallFb_NULL(0)
        EN_MemCallFb_Succeed(1)
        EN_MemCallFb_Faild(2)
        EN_MemCallFb_Wait(3)
        EN_MemCallFb_CleanS(4)
        EN_MemCallFb_CleanF(5)
        EN_MemCallFb_Res(6)
        EN_MemCallFb_Invalid(7)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMemCallFb.EN_MemCallFb_NULL;
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
