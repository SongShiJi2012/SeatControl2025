%% Create enMassageLevel_DSM enum

classdef enMassageLevel_DSM < Simulink.IntEnumType

    enumeration
        EN_OFF(0)
        EN_L1(1)
        EN_L2(2)
        EN_L3(3)
        EN_AUTO_OFF(4)
        EN_Inactive(5)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMassageLevel_DSM.EN_OFF;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'DSM请求档位、按摩模块反馈档位:&#10;0x0:OFF&#10;0x1:Level1&#10;0x2:Level2&#10;0x3:Level3&#10;0x4:AUTO  OFF自动关闭&#10;0x5:Inactive,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
