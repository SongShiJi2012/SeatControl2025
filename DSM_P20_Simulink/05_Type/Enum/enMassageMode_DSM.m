%% Create enMassageMode_DSM enum

classdef enMassageMode_DSM < Simulink.IntEnumType

    enumeration
        EN_M1(0)
        EN_M2(1)
        EN_M3(2)
        EN_M4(3)
        EN_M5(4)
        EN_M6(5)
        EN_M7(6)
        EN_M8(7)
        EN_MError(8)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMassageMode_DSM.EN_M1;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'DSM请求模式/按摩模块反馈模式:&#10;0x0:Mode1全身放松&#10;0x1:Mode2全身激活&#10;0x2:Mode3肩部激活&#10;0x3:Mode4肩部放松&#10;0x4:Mode5腰部激活&#10;0x5:Mode6腰部放松&#10;0x6:Mode7背部激活&#10;0x7:Mode8背部放松&#10;0x8:故障模式,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
