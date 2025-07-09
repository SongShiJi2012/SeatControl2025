%% Create enWelcomeSts enum

classdef enWelcomeSts < Simulink.IntEnumType

    enumeration
        EN_NULL(0)
        EN_BackwardStsSuccess(1)
        EN_ForwardStsSuccess(2)
        EN_BackMoveFail(3)
        EN_ForwardMoveFail(4)
        EN_BackMovingExForWard(5) 
        EN_ForWardMovingExBack(6) 
        EN_ExitWelcomeFun(7)
        EN_Wel_BWOngoing(8)
        EN_Wel_FWOngoing(9)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enWelcomeSts.EN_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'Ö÷¼ÝÓ­±öËù´¦×´Ì¬£º&#10;0x00: enNULL Ä¬ÈÏ³õÊ¼»¯×´Ì¬&#10;0x01: enBackwardSts ºóÒÆ×´Ì¬&#10;0x02: enForwardSts Ç°ÒÆ×´Ì¬,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
