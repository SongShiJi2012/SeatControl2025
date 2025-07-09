%% Create enBackGear enum

classdef enBackGear < Simulink.IntEnumType

    enumeration
        enNULL(0)
        enBackGear_0(1)
        enBackGear_1(2)
        enBackGear_2(3)
        enBackGear_3(4)
        enBackGear_4(5)
        enBackGear_5(6)
        enBackGear_6(7)
        enBackGear_7(8)
        enBackGear_8(9)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enBackGear.enNULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'enNULL���޿�����λ����&#10;enBackGear_0������0����&#10;enBackGear_1������1����&#10;enBackGear_2������2����&#10;enBackGear_3������3����&#10;enBackGear_4������4����&#10;enBackGear_5������5����&#10;enBackGear_6������6����&#10;enBackGear_7������7����&#10;enBackGear_8������8����,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
