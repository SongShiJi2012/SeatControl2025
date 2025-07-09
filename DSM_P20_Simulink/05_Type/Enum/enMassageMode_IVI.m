%% Create enMassageMode_IVI enum

classdef enMassageMode_IVI < Simulink.IntEnumType

    enumeration
        EN_Inactive(0)
        EN_M1(1)
        EN_M2(2)
        EN_M3(3)
        EN_M4(4)
        EN_M5(5)
        EN_M6(6)
        EN_M7(7)
        EN_M8(8)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMassageMode_IVI.EN_Inactive;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'IVI请求模式:&#10;0x0:Inactive&#10;0x1:Mode1全身放松&#10;0x2:Mode2全身激活&#10;0x3:Mode3肩部激活&#10;0x4:Mode4肩部放松&#10;0x5:Mode5腰部激活&#10;0x6:Mode6腰部放松&#10;0x7:Mode7背部激活&#10;0x8:Mode8背部放松,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
